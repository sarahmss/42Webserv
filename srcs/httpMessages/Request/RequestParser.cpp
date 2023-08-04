/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::RequestParser::RequestParser() { return ;}

FT::RequestParser::RequestParser(int socketFd)
{
	_body = "";
	_socketFd = socketFd;
	_parseRequest();
}

FT::RequestParser::RequestParser( const RequestParser & src ) { *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::RequestParser::~RequestParser() { return ; }


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::RequestParser &	FT::RequestParser::operator=( RequestParser const & rhs )
{
	if ( this != &rhs )
	{
		this->_body = rhs.getBody();
		this->_headers = rhs.getHeaders();
		this->_method = rhs.getMethod();
		this->_uri = rhs.getUri();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const FT::RequestParser &rhs)
{

	FT::HeadersType				headers = rhs.getHeaders();
	FT::HeadersType::iterator	it = headers.begin();

	std::cout << "Method: " << rhs.getMethod() << std::endl;
	std::cout << "URI: " << rhs.getUri() << std::endl;
	std::cout << "ProtocolVersion: " << rhs.getProtocolVersion() << std::endl;
	while (it != headers.end())
	{
		o << it->first << " " << it->second << std::endl;
		it++;
	}
	std::cout << "Body: " << rhs.getBody() << std::endl;
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	FT::RequestParser::_parseRequest(void)
{
	std::string	requestLine;

	for ( int i = 0; requestLine != CRLF; i++)
	{
		requestLine = getSockStreamLine(_socketFd);
		if (i == 0)
			_parseRequestLine(requestLine);
		else
			_parseHeader(requestLine);
	}
	_parseBody();
}

void	FT::RequestParser::_parseRequestLine(std::string RequestLine)
{
	std::stringstream	RequestLineStream(RequestLine);
	std::string			line;

	std::getline(RequestLineStream, line, ' ');
	_method = line;
	std::getline(RequestLineStream, line, ' ');
	_uri = line;
	std::getline(RequestLineStream, line, ' ');
	_protocolVersion = line;
}

void	FT::RequestParser::_parseHeader(const std::string Headers)
{
	std::stringstream	HeadersStream(Headers);
	std::string			line;

	while (getline(HeadersStream, line))
	{
		std::size_t pos = line.find(' ');
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1, std::string::npos);
		this->_headers.insert(RequestPairType(key, value));
	}
}

void	FT::RequestParser::_parseBody()
{
	Body	body(_socketFd, _headers);
	int		bodyStatus = body.parseBody();

	if (bodyStatus == EMPTYBODY)
		return ;
	if (bodyStatus == UNCHUNKED)
		_headers["filename:"] = body.getFileName();
	if (bodyStatus == CHUNKED)
		_headers["Content-Length:"] = body.getContentLength();
	_body = body.getBody();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	FT::RequestParser::getServerName() const
{
	std::string	host = getMapItem(_headers, "Host");
	return (host.substr(0, host.find(':')));
}

std::string	FT::RequestParser::getMethod() const
{
	return (_method);
}
std::string	FT::RequestParser::getUri() const
{
	return (_uri);
}
FT::HeadersType	FT::RequestParser::getHeaders() const
{
	return (_headers);
}

std::string	FT::RequestParser::getHeader(const std::string &HeaderName) const
{
	return (_headers.at(HeaderName));
}

std::string	FT::RequestParser::getBody() const
{
	return (_body);
}

std::string	FT::RequestParser::getProtocolVersion() const
{
	return (_protocolVersion);
}

/* ************************************************************************** */
