/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/24 00:25:20 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Handler::Handler(void) { return ; }

Handler::Handler(int clientSocket, ServerConf conf)
{
	response_code = "200";
	headerField = std::make_pair("", "");
	getResponsePath = std::make_pair("", ""); // body -> path
	_clientSocket = clientSocket;
	_conf = conf;
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Handler::~Handler() { return ;}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Handler::launch(void)
{
	_requestParsed = RequestParser(_clientSocket);

	_serverName = _requestParsed.getServerName();
	_uri = _requestParsed.getUri();
//	try
//	{
		_checkRequest();
		_selectLocation();
		if (_checkRedirection())
			return ;
		_checkMethod();
		_setBody();
//	}
//	catch (const std::exception & e)
//	{
//		return ;
//		// [LOGGING] e
//	}
}

bool	Handler::_checkRedirection(void)
{
	std::string	redirection;

	redirection = _location.getRedirection();
	if (redirection == "")
		return (false);
	headerField = std::make_pair("Location", redirection);
	response_code = "301";
	return (true);
}

void	Handler::_checkRequest()
{
	std::string	method = _requestParsed.getMethod();
	std::string	uri = _requestParsed.getUri();
	std::string	protocolVersion = _requestParsed.getProtocolVersion();
	if ( method == "" || uri == "" || protocolVersion == "") {
		response_code = "400";
		throw (std::invalid_argument("Invalid request [Missing arg in request line]"));
	}
}

void	Handler::_selectLocation(void)
{
	LocationQueueType	locations;

	locations = _checkLocation();
	if (locations.empty()) {
		response_code = "404";
		throw (std::invalid_argument("Location not found"));
	}
	_location = locations.top();
}


/*
	@brief: checks which configured locations on the server match the URI ​​of the current request.
*/
LocationQueueType	Handler::_checkLocation(void)
{
	LocationVecType		locations = _conf.getLocation();
	LocationQueueType	result;

	for (size_t i = 0; i < locations.size(); i++)
		if (_uri.find(_setPrefix(locations[i])) == 0)
			result.push(locations[i]);
	return (result);
}

std::string	Handler::_setPrefix(Location location)
{
	std::string prefix = location.getPrefix();

	if ((prefix != "/") && (*prefix.rbegin() == '/'))
		prefix.reserve(prefix.length() - 1);
	return (prefix);
}

void	Handler::_checkMethod(void)
{
	LocationMethodsType				methods;
	LocationMethodsType::iterator	found;

	methods = _location.getAllowedMethods();
	_method = _requestParsed.getMethod();
	found = methods.find(_method);
	if (found == methods.end())
	{
		if (isKnownMethod(_method) == false) {
			response_code = "501";
			throw(std::invalid_argument("Invalid request [Not Known Method]"));
		}
		response_code = "405";
		throw(std::invalid_argument("Method not allowed: " + _method));
	}
}


void	Handler::_setBody(void)
{
	std::string	path;

	path = _setPath();
	if (_checkCgi(path) == true)
		_launchCGI(path);
	else if (_method == "POST")
		_launchPost();
	else if (_method == "GET")
		_launchGet(path);
	else if (_method == "DELETE")
		_launchDelete(path);
}


std::string	Handler::_setPath(void)
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

bool	Handler::_checkCgi(std::string path)
{
	std::string	extension;
	Cgi			cgi;

	return true;
	if (_conf.getCgi().size() == 0 || _location.getCgi().size() == 0)
		return(false);
	if (isDirectory(path))
	{
		checkSlash(path);
		if (findIndex(path, _location.getIndex()))
			return (false);
	} else if (!isFile(path)) { // [LOGGING] 
		response_code = "404";
		throw (std::runtime_error("file not found [cgi]"));
	}
	extension = getExtension(path);
	if (_location.getCgi().size() != 0)
		cgi = _location.getCgi();
	else
		cgi = _conf.getCgi();
	if (!cgi.hasExtension(extension))
		return (false);
	return (true);
}

void	Handler::_launchPost(void)
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
			response_code = "500";
			throw (std::runtime_error("Failed to open file for writing"));
		}
		newFile.write(body.c_str(), body.length());
		if (newFile.fail()) {
			response_code = "500";
			throw std::runtime_error("Failed to write [POST]");
		}
		newFile.close();
		headerField = std::make_pair("Location", fileLocation);
		response_code = "201";
	}
}

void	Handler::_checkPayload(void)
{
	int	payloadMaxSize;
	int	bodyLength;

	bodyLength = _requestParsed.getContentLength();
	payloadMaxSize = _conf.getBodySize();
	if (_location.getBodySize())
		payloadMaxSize = _location.getBodySize();

	if (bodyLength > payloadMaxSize) {
		response_code = "413";
		throw (std::invalid_argument("Payload Too Large"));
	}
}


void	Handler::_launchGet(std::string path)
{
	if (isDirectory(path))
	{
		checkSlash(path);
		if (findIndex(path, _location.getIndex()) == true)
			getResponsePath = getFileContent(path);
		else if (_location.getAutoIndex())
			getResponsePath = getAutoIndexContent(path,
							_conf.getListen().getHost(),
							intToString(_conf.getListen().getPort()),
							_uri);
		else
			response_code = "404";
	}
	else if (isFile(path))
		getResponsePath = getFileContent(path);
}

void	Handler::_launchDelete(std::string path)
{
	std::cout << path;
	return ;
}

void	Handler::_launchCGI(std::string path) {
	FT::Cgi_handler cgi;
	std::map<std::string, std::string> env;

	response_code = "200";
	_prepare_env_map(env, path);
	getResponsePath = std::make_pair(
			cgi.cgi_handler(response_code, env, _requestParsed.getBody()),
			path);
}

void	Handler::_prepare_env_map(std::map<std::string, std::string> &env_map, std::string path) {
    env_map["DOCUMENT_ROOT"] = _conf.getRoot();
    env_map["HTTP_HOST"] = "";
    env_map["HTTP_REFERER"] = _requestParsed.getUri();
    env_map["HTTP_USER_AGENT"] = _requestParsed.getHeader("User-Agent:");
    env_map["PATH"] = "";
    env_map["QUERY_STRING"] = _uri.find_first_of("?");
    env_map["REMOTE_ADDR"] = "";
    env_map["REMOTE_HOST"] = "";
    env_map["REMOTE_PORT"] = "";
    env_map["REMOTE_USER"] = "";
    env_map["REMOTE_URI"] = _uri;
    env_map["SCRIPT_FILENAME"] = path;
    env_map["SCRIPT_NAME"] = _uri.substr(_uri.find_last_of("/"));
    env_map["SERVER_ADMIN"] = "I'm only a human after all";
    env_map["SERVER_NAME"] = _serverName;
    env_map["SERVER_PORT"] = cast_to_string(_conf.getListen().getPort());
    env_map["SERVER_SOFTWARE"] = "webserv";
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

RequestParser	Handler::getRequestParser(void)
{
	return (_requestParsed);
}
/* ************************************************************************** */
