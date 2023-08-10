/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:02:43 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/10 03:39:19 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/*
	@brief Return true if map contains key
*/
bool	FT::MapHasKey(FT::HeadersType map, std::string key)
{
	return (map.find(key) != map.end());
}

std::string	FT::getMapItem(FT::HeadersType map, std::string key)
{
	if (MapHasKey(map, (key)))
		return (map[(key)]);
	return ("");
}

void FT::checkSlash(std::string &path)
{
	if (*path.rbegin() != '/')
			path.append("/");
}

bool FT::findIndex(std::string &path, std::vector<std::string> indexes)
{
	if (indexes.size())
	{
		for (size_t i = 0; i < indexes.size(); i++)
		{
			if (isFile(path + indexes[i]))
			{
				path.append(indexes[i]);
				return (true);
			}
		}
	}
	return (false);
}

bool	FT::isKnownMethod(std::string method)
{
	std::vector<std::string>	Methods = {"HEAD", "GET", "POST",
											"PUT", "DELETE", "PATCH"};

	for (const std::string& knownMethod : Methods)
		if (method == knownMethod)
			return (true);
	return (false);
}

bool	FT::isDirectory(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFDIR))
		return (true);
	return (false);
}

bool FT::isFile(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFREG))
		return (true);
	return (false);
}

std::string	FT::getFilePath(std::string path, std::string filename)
{
	if (filename == "")
		throw (std::invalid_argument("Invalid Request [filename]"));
	return (path + filename);
}

std::string	FT::getFileLocation(std::string fileName, std::string fileLocation)
{
	checkSlash(fileLocation);
	return (getFilePath(fileLocation, fileName));
}

FT::strPairType	FT::getFileContent(std::string path)
{
	std::stringstream buffer;
	std::ifstream file(path.c_str());

	if (!file)
		throw (std::runtime_error("file not found"));
	buffer << file.rdbuf();
	return std::make_pair(buffer.str(), path);
}

FT::strPairType	FT::getAutoIndexContent(std::string path, std::string host, std::string port, std::string uri)
{
	std::string		body(AUTOINDEX_HTML_HEAD);
	DIR				*dir;
	struct dirent	*entry;

	body += OPEN_BODY_TITLE + uri + CLOSE_H1;
	dir = opendir(path.c_str());
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			checkSlash(uri);
			body +=	OPEN_ANCHOR_TAG +
					host + DIVIDER +
					port +
					uri +
					std::string(entry->d_name) +
					MIDDLE_ANCHOR_TAG + entry->d_name +CLOSE_ANCHOR_TAG;
		}
	}
	body += CLOSE_BODY;
	closedir(dir);
	return (std::make_pair(body, path));
}


std::string	FT::getSockStreamLine(int socketFd)
{
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	Line;

	while (true)
	{
		bytes = recv(socketFd, buffer, 1, 0);
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
