/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:55:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/24 15:26:40 by smodesto         ###   ########.fr       */
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
	FileType	file;

	for (size_t i = 0; i < chunkSize; i++)
	{
		bodyLine += getSockStreamLine(_socketFd);
		length += chunkSize;
		getSockStreamLine(_socketFd);
		chunkSize = _getChunkSize();
	}
	_body = bodyLine;
	_ContentLenght = length;
	file.fileContet = _body;
	file.fileName = _fileName;
	_files.push_back(file);

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

	while (length > 0)
	{
		bytes = recv(_socketFd, buffer, BUFFSIZE, 0);
		if (bytes == -1)
			throw (std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			break;
		length -= bytes;
		temp.append(buffer, bytes);
		memset(buffer, 0, BUFFSIZE);
	}
	_boundary = temp.substr(0, temp.find(CRLF));
	temp.erase(0, temp.find(CRLF));
	_getBodyMessage(temp);
	return (UNCHUNKED);
}

void	Body::_getBodyMessage(std::string &Body)
{
	std::vector<std::string>	splitted_content;
	FileType					file;

	tokenize(Body, _boundary, splitted_content);
	if (IsMultipartForm() == true)
	{
		for (size_t i = 0; i < splitted_content.size() - 1; i++)
		{
			_ClearHeader(splitted_content[i]);
			file.fileContet = splitted_content[i];
			file.fileName = _fileName;
			_files.push_back(file);
			_body += splitted_content[i];
		}
	}
}

bool Body::IsMultipartForm(void)
{
	std::string	contentType;

	contentType = getMapItem(_headers, "Content-Type:");
	return (contentType.find("multipart/form-data") != std::string::npos);
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

FilesType	Body::getFiles(void)
{
	return (_files);
}

std::string	Body::getBody(void)
{
	return (_body);
}

int	Body::getContentLength(void)
{
	return (_ContentLenght);
}
/* ************************************************************************** */
