/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/10 03:40:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Handler::Handler(int clientSocket, ServerConf conf)
{
	_clientSocket = clientSocket;
	_conf = conf;
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Handler::~Handler() { return ;}

/*
** --------------------------------- METHODS ----------------------------------
*/
void	FT::Handler::launch(void)
{
	_requestParsed = RequestParser(_clientSocket);

	_serverName = _requestParsed.getServerName();
	_uri = _requestParsed.getUri();
	_checkRequest();
	_selectLocation();
	if (_checkRedirection())
		return ;
	_checkMethod();
	_setBody();
}

bool	FT::Handler::_checkRedirection(void)
{
	std::string	redirection;

	redirection = _location.getRedirection();
	if (redirection == "")
		return (false);
	headerField = std::make_pair("Location", redirection);
	codeDescription = std::make_pair("301", "Moved Permanently");
}

void	FT::Handler::_checkRequest(void)
{
	if (_requestParsed.getMethod() == "" ||
		_requestParsed.getUri() == "" ||
		_requestParsed.getProtocolVersion() == "")
		throw(std::invalid_argument("Invalid request"));
}

void	FT::Handler::_selectLocation(void)
{
	LocationQueueType	locations;

	locations = _checkLocation();
	if (locations.empty())
		throw (std::invalid_argument("Location not found"));
	_location = locations.top();
}


/*
	@brief: checks which configured locations on the server match the URI ​​of the current request.
*/
LocationQueueType	FT::Handler::_checkLocation(void)
{
	LocationVecType		locations = _conf.getLocation();
	LocationQueueType	result;

	for (size_t i = 0; i < locations.size(); i++)
		if (_uri.find(_setPrefix(locations[i])) == 0)
			result.push(locations[i]);
	return (result);
}

std::string	FT::Handler::_setPrefix(Location location)
{
	std::string prefix = location.getPrefix();

	if ((prefix != "/") && (*prefix.rbegin() == '/'))
		prefix.reserve(prefix.length() - 1);
	return (prefix);
}

void	FT::Handler::_checkMethod(void)
{
	LocationMethodsType				methods;
	LocationMethodsType::iterator	found;

	methods = _location.getAllowedMethods();
	_method = _requestParsed.getMethod();
	found = methods.find(_method);
	if (found == methods.end())
	{
		if (isKnownMethod(_method) == false)
			throw(std::invalid_argument("Invalid request"));
		throw(std::invalid_argument("Method not allowed: " + _method));
	}
}

void	FT::Handler::_setBody(void)
{
	std::string	path;

	path = _setPath();
	if (_method == "POST")
		_launchPost();
	else if (_method == "GET")
		_launchGet(path);
	else if (_method == "DELETE")
		_launchDelete(path);
}


std::string	FT::Handler::_setPath(void)
{
	std::string	path;
	std::string	prefix;
	std::string	resource;

	if (_location.getRoot() != "") {
		path = _location.getRoot();
		prefix = _location.getPrefix();
		resource = _uri.substr(_uri.find(prefix) + prefix.length(), _uri.npos);
		checkSlash(path);
		path.append(resource);
	} else
		path = _conf.getRoot() + _uri;
	return(path);
}

void	FT::Handler::_launchPost(void)
{
	std::ofstream	newFile;
	std::string		body;
	std::string		filePath;
	std::string		fileLocation;

	_checkPayload();
	if (_requestParsed.IsMultipartForm())
	{
		filePath = getFilePath(_setPath(),
						_requestParsed.getHeader("filename"));
		fileLocation = getFileLocation(_requestParsed.getHeader("filename"),
						(_conf.getRoot() + _uri));
		body = _requestParsed.getBody();
		newFile.open(filePath.c_str(), std::ios::binary);
		if (!newFile.is_open())
		{
			throw (std::runtime_error("Failed to open file for writing"));
			return ;
		}
		newFile.write(body.c_str(), body.length());
		if (newFile.fail())
			throw std::runtime_error("Failed to write [POST]");
		newFile.close();
		headerField = std::make_pair("Location", fileLocation);
		codeDescription = std::make_pair("201", "Created");
	}
}

void	FT::Handler::_checkPayload(void)
{
	int	payloadMaxSize;
	int	bodyLength;

	bodyLength = _requestParsed.getContentLength();
	payloadMaxSize = _conf.getBodySize();
	if (_location.getBodySize())
		payloadMaxSize = _location.getBodySize();

	if (bodyLength > payloadMaxSize)
		throw (std::invalid_argument("Payload Too Large"));
}


void	FT::Handler::_launchGet(std::string path)
{
	if (isDirectory(path))
	{
		checkSlash(path);
		if (findIndex(path, _location.getIndex()) == true)
			getResponsePath = getFileContent(path);
		else if (_location.getAutoIndex())
			getResponsePath = getAutoIndexContent(path,
							_conf.getListen().getHost(),
							_conf.getListen().getPort(),
							_uri);
		else
			codeDescription = std::make_pair("404", "Not Found");
	}
	else if (isFile(path))
		getResponsePath = getFileContent(path);
}

void	FT::Handler::_launchDelete(std::string path)
{
	return ;
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::RequestParser	FT::Handler::getRequestParser(void)
{
	return (_requestParsed);
}
/* ************************************************************************** */
