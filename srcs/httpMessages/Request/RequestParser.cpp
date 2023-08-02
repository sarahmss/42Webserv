/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/01 23:50:45 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::RequestParser::RequestParser() { return ;}

FT::RequestParser::RequestParser(int socketFd)
{
	_socketFd = socketFd;
	parseRequest();
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
	std::cout << "Body: " << rhs.GetBody() << std::endl;
	std::cout << "Headers:";
	while (it != headers.end())
	{
		o << it->first << " " << it->second << std::endl;
		it++;
	}
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string	FT::RequestParser::_GetRequestLine()
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

void	FT::RequestParser::parseRequest(void)
{
	std::string	requestLine;

	for ( int i = 0; requestLine != CRLF; i++)
	{
		requestLine = _GetRequestLine();
		if (i == 0)
			parseRequestLine(requestLine);
		else
			parseHeader(requestLine);
	}
	parseBody();
}

void	FT::RequestParser::parseRequestLine(std::string RequestLine)
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

void	FT::RequestParser::parseHeader(const std::string Headers)
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

void	FT::RequestParser::parseBody(void)
{
	if (MapHasKey(_headers, "Content-Length:" ) == false
		|| MapHasKey(_headers, "Transfer-Encoding: ") == false)
		return;
	if (GetMapItem(_headers, "Transfer-Encoding:") == "chunked")
		_HandleChunckedBody();
	else if (MapHasKey(_headers, "Content-Length:"))
		_ReadMessageBody();
}

void	FT::RequestParser::_HandleChunckedBody(void)
{
	std::cout << "Handle chuncked body Not implemented" << std::endl;
}

void	FT::RequestParser::_ReadMessageBody(void)
{
	int			length = atoi(GetMapItem(_headers, "Content-Length:").c_str());
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	bodyLine;

	while (length > 0)
	{
		bytes = recv(_socketFd, buffer, BUFFSIZE, 0);
		if (bytes == -1)
			throw(std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			break;
		length -= bytes;
		bodyLine.append(buffer, bytes);
		memset(buffer, 0, BUFFSIZE);
	}
	_GetBodyMessage(bodyLine);
}

void	FT::RequestParser::_GetBodyMessage(std::string &Body)
{
	if (_IsMultipartFormData() == true)
	{
		_ClearHeader(Body);
		_ClearFooter(Body);
	}
	_body = Body;
}

bool FT::RequestParser::_IsMultipartFormData(void)
{
	std::string	contentType;

	contentType = GetMapItem(_headers, "Content-Type:");
	return (contentType.find("multipart/form-data:") != std::string::npos);
}


void	FT::RequestParser::_ClearFooter(std::string &Body)
{
	std::string	footer;

	footer = Body.substr(Body.rfind(CRLF), Body.npos);
	Body.erase(Body.length() - footer.length(), Body.npos);
}

void	FT::RequestParser::_ClearHeader(std::string &Body)
{
	std::string	header;

	header = Body.substr(0, Body.find(CRLF2X));
	_GetFileName(header);
	Body.erase(0, header.length() + 4);
}

void	FT::RequestParser::_GetFileName(std::string header)
{
	std::string	filename;
	size_t	begin;
	size_t	end;

	begin = header.find("filename=\"") + 11;
	end = header.find("\"", begin);
	filename = header.substr(begin, (end - begin));
	_headers["filename:"] = filename;
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
