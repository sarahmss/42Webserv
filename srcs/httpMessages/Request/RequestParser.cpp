/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/21 13:28:28 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"
#include <stdexcept>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RequestParser::RequestParser() { return ;}

RequestParser::RequestParser(int socketFd)
{
	_method = "";
	_protocolVersion = "";
	_uri = "";
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
		this->_files = rhs.getFiles();
		this->_body = rhs.getBody();
		this->_headers = rhs.getHeaders();
		this->_method = rhs.getMethod();
		this->_uri = rhs.getUri();
		this->_protocolVersion = rhs.getProtocolVersion();
		this->_multPart = rhs.getMultPart();
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
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
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
	std::getline(RequestLineStream, line, ' ');
	_method = line;
	std::getline(RequestLineStream, line, ' ');
	_uri = line;
	std::getline(RequestLineStream, line, '\r');
	_protocolVersion = line;

	if (_method == "" || _uri == "" || _protocolVersion == "")
		throw std::runtime_error("Empty or incomplete RequestLine");
}

void	RequestParser::_parseHeader(const std::string Headers)
{
	std::stringstream	HeadersStream(Headers);
	std::string			line;

	sendMessageToLogFile("Parsing headers | requestParser->_parseHeader", true, 0);
	if (!getline(HeadersStream, line))
		throw std::runtime_error("Empty request header field");
	else
		do {
			std::size_t pos = line.find(' ');
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1, std::string::npos);
			this->_headers.insert(RequestPairType(key, value));
		}
		while(getline(HeadersStream, line));
}

void	RequestParser::_parseBody()
{
	Body	body(_socketFd, _headers);
	int		bodyStatus = body.parseBody();
	std::string	fileNames;

	// Informação do estado do body, empty, chunked, unchucked [LOGGING]
	sendMessageToLogFile("Parsing body: " + intToString(bodyStatus), true, 0);
	_files = body.getFiles();
	if (bodyStatus == EMPTYBODY)
		return ;
	if (bodyStatus == UNCHUNKED)
	{
		for (size_t i = 0; i < _files.size(); i++)
			fileNames += _files[i].fileName + " ";
		_headers["Filename"] = fileNames;
	}
	if (bodyStatus == CHUNKED)
		_headers["Content-Length:"] = intToString(body.getContentLength());
	_body = body.getBody();
	_multPart = body.IsMultipartForm();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


bool	RequestParser::getMultPart(void) const
{
	return (_multPart);
}

FilesType	RequestParser::getFiles(void) const
{
	return (_files);
}

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
