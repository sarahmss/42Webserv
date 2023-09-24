/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:02:43 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/23 21:01:23 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <sys/socket.h>

/*
	@brief Return true if map contains key
*/
bool	MapHasKey(HeadersType map, std::string key)
{
	return (map.find(key) != map.end());
}

std::string	getMapItem(HeadersType map, std::string key)
{
	if (MapHasKey(map, (key)))
		return (map[(key)]);
	return ("");
}

void checkSlash(std::string &path)
{
	if (*path.rbegin() != '/')
			path.append("/");
}

bool findIndex(std::string &path, std::vector<std::string> indexes)
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

std::string	getExtension(std::string path)
{
	size_t pos;
	size_t size;

	pos = path.rfind(".");
	if (pos == std::string::npos)
		return ("");
	size = path.size();
	return (path.substr(pos + 1, size));
}

std::string intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void tokenize(std::string const &str, std::string delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool	isKnownMethod(std::string method)
{
	std::string Methods[7] = {"HEAD", "GET", "POST", "PUT", "DELETE", "PATCH"};

	for (int i = 0; i < 7; i++)
		if (method == Methods[i])
			return (true);
	return (false);
}

bool	isDirectory(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFDIR))
		return (true);
	return (false);
}

void CreateDirectory(std::string fileName, std::string filePath)
{
	std::string	dirName;
	int			check;

	dirName = filePath.erase(filePath.find(fileName));
	if (!isDirectory(dirName))
	{
		check = mkdir(dirName.c_str(), 0777);
		if (check)
			throw (std::runtime_error("Unable to create directory\n"));
	}
}


std::string CreateFile(std::string filePath, std::string body)
{
	std::ofstream	newFile;
	std::string		responseCode = "201";

	newFile.open(filePath.c_str(), std::ios::binary);
	if (!newFile.is_open())
	{
		responseCode = "500";
		throw (std::runtime_error("Failed to open file for writing"));
	}
	newFile.write(body.c_str(), body.length());
	if (newFile.fail()) {
		responseCode = "500";
		throw std::runtime_error("Failed to write [POST]");
	}
	newFile.close();
	return (responseCode);
}

bool isFile(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFREG))
		return (true);
	return (false);
}

std::string	getFilePath(std::string path, std::string filename)
{
	if (filename == "")
		throw (std::invalid_argument("Invalid Request [filename]"));
	return (path + "/" + filename);
}

std::string	getFileLocation(std::string fileName, std::string fileLocation)
{
	checkSlash(fileLocation);
	return (fileLocation + fileName);
}

strPairType	getFileContent(std::string path)
{
	std::stringstream buffer;
	std::ifstream file(path.c_str());

	if (!file)
		throw (std::runtime_error("file not found"));
	buffer << file.rdbuf();
	return std::make_pair(buffer.str(), path);
}

strPairType	getAutoIndexContent(std::string path, std::string host, std::string port, std::string uri)
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

bool live(bool status)
{
	static bool mode = true;
	if (!status)
		mode = false;
	return mode;
}

void	sigHandler(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		live(false);
}

std::string	getSockStreamLine(int socketFd)
{
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	Line;

	while (true)
	{
		bytes = recv(socketFd, buffer, 1, 0);
		if (bytes == -1)
			throw (std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			close(socketFd); // check
		Line += buffer;
		if (Line.rfind(CRLF) != std::string::npos)
			break;
	}
	return (Line);
}

std::string cast_to_string(int num) {
    std::ostringstream out_stream;
    out_stream << num;
    return (out_stream.str());
}
