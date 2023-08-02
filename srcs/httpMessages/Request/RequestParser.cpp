/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/02 00:28:27 by smodesto         ###   ########.fr       */
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
		this->_request = rhs.GetRequest();
		this->_body = rhs.GetBody();
		this->_headers = rhs.GetHeaders();
		this->_method = rhs.GetMethod();
		this->_uri = rhs.GetUri();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const FT::RequestParser &rhs)
{

	FT::HeadersType				headers = rhs.GetHeaders();
	FT::HeadersType::iterator	it = headers.begin();

	std::cout << "Method: " << rhs.GetMethod() << std::endl;
	std::cout << "URI: " << rhs.GetUri() << std::endl;
	std::cout << "ProtocolVersion: " << rhs.GetProtocolVersion() << std::endl;
	while (it != headers.end())
	{
		o << it->first << " " << it->second << std::endl;
		it++;
	}
	std::cout << "Body: " << rhs.GetBody() << std::endl;
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string	FT::RequestParser::_getRequestLine()
{
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	Line;

	while (true)
	{
		bytes = recv(_socketFd, buffer, 1, 0);
		if (bytes == -1)
			throw(std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			break;
		Line.append(buffer, bytes);
		memset(buffer, 0, BUFFSIZE);
		if (Line.rfind(CRLF) != std::string::npos)
			break;
	}
	return (Line);
}

void	FT::RequestParser::_parseRequest(void)
{
	std::string	requestLine;

	for ( int i = 0; requestLine != CRLF; i++)
	{
		requestLine = _getRequestLine();
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

	if (body.parseBody() == -1)
		return ;
	_body = body.GetBody();
	_headers["filename:"] = body.GetFileName();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


std::string	FT::RequestParser::GetRequest() const
{
	return (_request);
}
std::string	FT::RequestParser::GetMethod() const
{
	return (_method);
}
std::string	FT::RequestParser::GetUri() const
{
	return (_uri);
}
FT::HeadersType	FT::RequestParser::GetHeaders() const
{
	return (_headers);
}

std::string	FT::RequestParser::GetHeader(const std::string &HeaderName) const
{
	return (_headers.at(HeaderName));
}

std::string	FT::RequestParser::GetBody() const
{
	return (_body);
}

std::string	FT::RequestParser::GetProtocolVersion() const
{
	return (_protocolVersion);
}

/* ************************************************************************** */
