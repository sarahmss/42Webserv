/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:55:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/02 00:43:33 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Body.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Body::Body(int socketFd, HeadersType headers)
 {
	_socketFd = socketFd;
	_headers = headers;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Body::~Body() { return ; }


/*
** --------------------------------- METHODS ----------------------------------
*/

int	FT::Body::parseBody(void)
{
	if (MapHasKey(_headers, "Content-Length:" ) == false
		|| MapHasKey(_headers, "Transfer-Encoding: ") == false)
		return (-1);
	if (GetMapItem(_headers, "Transfer-Encoding:") == "chunked")
		_HandleChunckedBody();
	else if (MapHasKey(_headers, "Content-Length:"))
		_ReadMessageBody();
	return (1);
}

void	FT::Body::_HandleChunckedBody(void)
{
/*	int			length = 0;
	ssize_t		chunckSize = _getChunckSize();
	std::string	bodyLine;*/


}


ssize_t	FT::Body::_getChunckSize(void)
{
	return (1);
}

void	FT::Body::_ReadMessageBody(void)
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

void	FT::Body::_GetBodyMessage(std::string &Body)
{
	if (_IsMultipartFormData() == true)
	{
		_ClearHeader(Body);
		_ClearFooter(Body);
	}
	_body = Body;
}

bool FT::Body::_IsMultipartFormData(void)
{
	std::string	contentType;

	contentType = GetMapItem(_headers, "Content-Type:");
	return (contentType.find("multipart/form-data:") != std::string::npos);
}


void	FT::Body::_ClearFooter(std::string &Body)
{
	std::string	footer;

	footer = Body.substr(Body.rfind(CRLF), Body.npos);
	Body.erase(Body.length() - footer.length(), Body.npos);
}

void	FT::Body::_ClearHeader(std::string &Body)
{
	std::string	header;

	header = Body.substr(0, Body.find(CRLF2X));
	_GetFileName(header);
	Body.erase(0, header.length() + 4);
}

void	FT::Body::_GetFileName(std::string header)
{
	std::string	filename;
	size_t	begin;
	size_t	end;

	begin = header.find("filename=\"") + 11;
	end = header.find("\"", begin);
	filename = header.substr(begin, (end - begin));
	_fileName = filename;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	FT::Body::GetBody(void)
{
	return (_body);
}

std::string	FT::Body::GetFileName(void)
{
	return (_body);
}

/* ************************************************************************** */
