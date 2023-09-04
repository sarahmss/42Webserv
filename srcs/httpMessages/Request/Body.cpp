/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:55:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/02 17:58:16 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Body.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Body::Body(int socketFd, HeadersType headers)
 {
	_socketFd = socketFd;
	_headers = headers;
	_unparsed = "";
	_ContentLenght = 0;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Body::~Body() { return ; }


/*
** --------------------------------- METHODS ----------------------------------
*/

int	Body::parseBody(void)
{
	std::string encoding;

	if (MapHasKey(_headers, "Content-Length:" ) == false
		&& MapHasKey(_headers, "Transfer-Encoding:") == false)
		return (EMPTYBODY);
	encoding = getMapItem(_headers, "Transfer-Encoding:");
	if (encoding.find("chunked") != encoding.npos)
		return (_HandleChunkedBody());
	else if (MapHasKey(_headers, "Content-Length:"))
		return(_ReadMessageBody());
	return (0);
}

int	Body::_HandleChunkedBody(void)
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


size_t	Body::_getChunkSize(void)
{
	std::string	chunkSizeLine = getSockStreamLine(_socketFd);
	size_t		pos;

	if (chunkSizeLine.empty())
		return (0);
	pos = chunkSizeLine.find(" ");
	return (_convertChunkSize(chunkSizeLine.substr(0, pos)));
}

size_t	Body::_convertChunkSize(std::string chunkSize)
{
	std::size_t			size;
	std::stringstream	chunkStream(chunkSize);

	chunkStream >> std::hex >> size;
	return (size);
}

int	Body::_ReadMessageBody(void)
{
	int			length = atoi(getMapItem(_headers, "Content-Length:").c_str());
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	temp;

	std::cout << "---------------------------Unchunked----------------------\n";
	while (length > 0)
	{
		bytes = recv(_socketFd, buffer, BUFFSIZE, 0);
		if (bytes == -1)
			throw(std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			break;
		length -= bytes;
		temp.append(buffer, bytes);
		memset(buffer, 0, BUFFSIZE);
	}
	_getBodyMessage(temp);
	return (UNCHUNKED);
}

void	Body::_getBodyMessage(std::string &Body)
{
	if (IsMultipartForm() == true)
	{
		_ClearHeader(Body);
		_ClearBoundary(Body);
	}
	_body = Body;
}

bool Body::IsMultipartForm(void)
{
	std::string	contentType;

	contentType = getMapItem(_headers, "Content-Type:");
	return (contentType.find("multipart/form-data") != std::string::npos);
}


void	Body::_ClearBoundary(std::string &Body)
{
	int			begin = Body.rfind("\n-");
	int			end = Body.rfind("--");

	Body.erase(begin, begin - end);
}

void	Body::_ClearHeader(std::string &Body)
{
	std::string	header;

	header = Body.substr(0, Body.find(CRLF2X));
	_getFileName(header);
	Body.erase(0, header.length() + 4);
}

void	Body::_getFileName(std::string header)
{
	std::string	filename;
	size_t	begin;
	size_t	end;

	begin = header.find("filename=\"") + 10;
	end = header.find("\"", begin);
	filename = header.substr(begin, (end - begin));
	_fileName = filename;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	Body::getBody(void)
{
	return (_body);
}

std::string	Body::getFileName(void)
{
	return (_fileName);
}

int	Body::getContentLength(void)
{
	return (_ContentLenght);
}
/* ************************************************************************** */
