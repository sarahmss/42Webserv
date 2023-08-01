/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 23:11:33 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::RequestParser::RequestParser() { return ;}

FT::RequestParser::RequestParser( const std::string &request )
{
	_request = request;
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



void	FT::RequestParser::parseRequest(void)
{
	std::string request = _request;
	std::string line;

	size_t pos = 0;
	while ((pos = request.find(CRLF)) != std::string::npos) {
		line = request.substr(0, pos);
		request.erase(0, pos + 2);
		if (line.empty() || line.find_first_not_of(" \t") == std::string::npos)
			break;

		if (line.find(":") != std::string::npos)
			parseHeader(line);
		else
			parseRequestLine(line);
	}
	parseBody(line);
}

void	FT::RequestParser::parseRequestLine(const std::string RequestLine)
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

void	FT::RequestParser::parseBody(const std::string Body)
{
	if (MapHasKey(_headers, "Content-Length:" ) == false
		|| MapHasKey(_headers, "Transfer-Encoding: ") == false)
		return;
	if (GetMapItem(_headers, "Transfer-Encoding:") == "chunked")
		_body = _HandleChunckedBody(Body);
	else if (MapHasKey(_headers, "Content-Length:"))
		_body = _ReadMessageBody(Body);
}

std::string	FT::RequestParser::_HandleChunckedBody(const std::string Body)
{
	std::cout << "Handle chuncked body Not implemented" << Body << std::endl;
	return (Body);
}
std::string	FT::RequestParser::_ReadMessageBody(const std::string Body)
{
	std::cout << "Read message body Not implemented" << Body << std::endl;
	return (Body);
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
