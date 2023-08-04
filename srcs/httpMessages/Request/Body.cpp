/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:55:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:39 by smodesto         ###   ########.fr       */
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
		return (EMPTYBODY);
	if (getMapItem(_headers, "Transfer-Encoding:") == "chunked")
		return (_HandleChunkedBody());
	else if (MapHasKey(_headers, "Content-Length:"))
		return(_ReadMessageBody());
	return (0);
}

int	FT::Body::_HandleChunkedBody(void)
{
	int			length = 0;
	size_t		chunkSize = _getChunkSize();
	std::string	bodyLine = "";

	for (size_t i = 0; i < chunkSize; i++)
	{
		bodyLine += getSockStreamLine(_socketFd);
		length += chunkSize;
		chunkSize = _getChunkSize();
	}
	_body = bodyLine;
	_ContentLenght = length;
	return (CHUNKED);
}


size_t	FT::Body::_getChunkSize(void)
{
	std::string	chunkSizeLine = getSockStreamLine(_socketFd);
	size_t		pos;

	if (chunkSizeLine.empty())
		return (0);
	pos = chunkSizeLine.find(" ");
	return (_convertChunkSize(chunkSizeLine.substr(0, pos)));
}

size_t	FT::Body::_convertChunkSize(std::string chunkSize)
{
	std::size_t			size;
	std::stringstream	chunkStream(chunkSize);

	chunkStream >> std::hex >> size;
	return (size);
}

int	FT::Body::_ReadMessageBody(void)
{
	int			length = atoi(getMapItem(_headers, "Content-Length:").c_str());
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
	_getBodyMessage(bodyLine);
	return (UNCHUNKED);
}

void	FT::Body::_getBodyMessage(std::string &Body)
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

	contentType = getMapItem(_headers, "Content-Type:");
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
	_getFileName(header);
	Body.erase(0, header.length() + 4);
}

void	FT::Body::_getFileName(std::string header)
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

std::string	FT::Body::getBody(void)
{
	return (_body);
}

std::string	FT::Body::getFileName(void)
{
	return (_body);
}

int	FT::Body::getContentLength(void)
{
	return (_ContentLenght);
}
/* ************************************************************************** */
