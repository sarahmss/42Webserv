/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/30 21:53:29 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RequestParser::RequestParser() { return ;}

RequestParser::RequestParser(int socketFd)
{
	_method = "";
	_protocolVersion = "";
	_uri = "";
	_body = "";
	_socketFd = socketFd;
	_parseRequest();
	sendMessageToLogFile("Request Parsed | RequestParser->RequestParser ", false, 0);
	std::cout << " ++ Request Parsed" << std::endl;
}

RequestParser::RequestParser( const RequestParser & src ) { *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RequestParser::~RequestParser() { return ; }


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RequestParser &	RequestParser::operator=( RequestParser const & rhs )
{
	if ( this != &rhs )
	{
		this->_body = rhs.getBody();
		this->_headers = rhs.getHeaders();
		this->_method = rhs.getMethod();
		this->_uri = rhs.getUri();
		this->_protocolVersion = rhs.getProtocolVersion();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const RequestParser &rhs)
{

	HeadersType				headers = rhs.getHeaders();
	HeadersType::iterator	it = headers.begin();

	o << "Method: " << rhs.getMethod() << std::endl;
	o << "URI: " << rhs.getUri() << std::endl;
	o << "ProtocolVersion: " << rhs.getProtocolVersion() << std::endl;
	while (it != headers.end())
	{
		o << it->first << " " << it->second << std::endl;
		it++;
	}
	o << "Body: " << rhs.getBody() << std::endl;
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	RequestParser::_parseRequest(void)
{
	std::string	requestLine;

	sendMessageToLogFile("Parsing request | requestParser->_parseRequest", true, 0);
	std::cout << "++Parsing request..." << std::endl;
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

void	RequestParser::_parseRequestLine(std::string RequestLine)
{
	std::stringstream	RequestLineStream(RequestLine);
	std::string			line;

	sendMessageToLogFile("Parsing RequestLine | requestParser->_parseRequestLine", true, 0);
	std::cout << " ++ Parsing RequestLine" << std::endl;
	std::getline(RequestLineStream, line, ' ');
	_method = line;
	std::getline(RequestLineStream, line, ' ');
	_uri = line;
	std::getline(RequestLineStream, line, '\r');
	_protocolVersion = line;
}

void	RequestParser::_parseHeader(const std::string Headers)
{
	std::stringstream	HeadersStream(Headers);
	std::string			line;

	sendMessageToLogFile("Parsing headers | requestParser->_parseHeader", true, 0);
//	std::cout << " ++ Parsing headers" << std::endl;
	while (getline(HeadersStream, line))
	{
		std::size_t pos = line.find(' ');
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1, std::string::npos);
		this->_headers.insert(RequestPairType(key, value));
	}
}

void	RequestParser::_parseBody()
{
	Body	body(_socketFd, _headers);
	int		bodyStatus = body.parseBody();

	sendMessageToLogFile("Parsing body | requestParser->_parseBody", true, 0);
	std::cout << " ++ Parsing body" << std::endl;
	if (bodyStatus == EMPTYBODY)
	{
		sendMessageToLogFile("Error EMPTY BODY | requestParser->_parseBody", false, 0);
		return ;
	}
	if (bodyStatus == UNCHUNKED)	// [LOGGING] body stts // preciso sanar dúvidas com a sarah
		_headers["filename:"] = body.getFileName();
	if (bodyStatus == CHUNKED)		// [LOGGING] body stts // preciso sanar dúvidas com a sarah
		_headers["Content-Length:"] = body.getContentLength();
	_body = body.getBody();
	_multPart = body.IsMultipartForm();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	RequestParser::getServerName() const
{
	std::string	host = getMapItem(_headers, "Host");
	return (host.substr(0, host.find(':')));
}

std::string	RequestParser::getMethod() const
{
	return (_method);
}

std::string	RequestParser::getProtocolVersion() const
{
	return (_protocolVersion);
}

std::string	RequestParser::getUri() const
{
	return (_uri);
}
HeadersType	RequestParser::getHeaders() const
{
	return (_headers);
}

std::string	RequestParser::getHeader(const std::string &HeaderName) const
{
	return (_headers.at(HeaderName));
}

std::string	RequestParser::getBody() const
{
	return (_body);
}

int			RequestParser::getContentLength(void) const
{
	return (atoi(_headers.at("Content-Length:").c_str()));
}

bool RequestParser::IsMultipartForm()
{
	return(_multPart);
}
/* ************************************************************************** */
