/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:41:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/10/03 21:33:54 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
#include <map>
#include <vector>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
# include <stdlib.h>
# include <string.h>
#include <sys/stat.h>
#include <dirent.h>
# include <csignal>
#include <ctime>


#define CRLF "\r\n"
#define CRLF2X "\r\n\r\n"
#define BUFFSIZE 2

#define AUTOINDEX_HTML_HEAD "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\"content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Autoindex</title></head>"
#define CLOSE_BODY "</body></html>"
#define CLOSE_H1 "</h1>"
#define OPEN_BODY_TITLE "<body><h1>Index of "
#define OPEN_ANCHOR_TAG "<p><a href=\"http://"
#define MIDDLE_ANCHOR_TAG "\">"
#define CLOSE_ANCHOR_TAG "</a></p>"
#define SLASH "/"
#define DIVIDER ":"
#define DELETE_HTML	"<html><body><h1>Arquivo removido.</h1></body></html>"

enum MimeType
{
	JPEG,
	PNG,
	GIF,
	TXT, //plain
	HTML,
	CSS,
	JS,
	ICO,
	Unknown
};

typedef struct s_files
{
	std::string	fileName;
	std::string	fileContet;
}	t_files;

typedef t_files	FileType;
typedef std::vector<t_files>	FilesType;

typedef std::pair<std::string, std::string> strPairType;
typedef std::vector<strPairType> vecPairType;
typedef std::pair<std::string, std::string>	RequestPairType;

typedef std::map<std::string, std::string>	HeadersType;

bool		MapHasKey(HeadersType map, std::string key);
bool		isKnownMethod(std::string method);
bool		isValidMethod(std::string method);
bool		isDirectory(std::string path);
bool		isFile(std::string path);
bool		findIndex(std::string &path, std::vector<std::string> indexes);
void		checkSlash(std::string &path);
void		CreateDirectory(std::string fileName, std::string filePath);
std::string	CreateFile(std::string filePath, std::string body);

std::string	cast_to_string(int num);
std::string	intToString(int value);
std::string	getMapItem(HeadersType map, std::string key);
std::string	getSockStreamLine(int socketFd);
std::string	getFilePath(std::string path, std::string filename);
std::string	getFileLocation(std::string fileName, std::string fileLocation);
strPairType	getFileContent(std::string path);
strPairType	getAutoIndexContent(std::string path, std::string host, std::string port, std::string uri);
std::string	getExtension(std::string path);

bool	live(bool status);
void	sigHandler(int signal);
void	tokenize(std::string const &str, std::string delim,
		std::vector<std::string> &out);
MimeType	setContentType(std::string path);

#endif // UTILS_HPP
