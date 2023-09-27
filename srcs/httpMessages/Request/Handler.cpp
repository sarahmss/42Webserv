/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/27 19:38:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler.hpp"
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Handler::Handler(void) { return ; }

Handler::Handler(int clientSocket, ServerConf conf, struct sockaddr_in &address)
{
	response_code = "200";
	headerField = std::make_pair("", "");
	Response = std::make_pair("", ""); // body -> path
	_clientSocket = clientSocket;
	_conf = conf;
	_client_port = ntohs(address.sin_port);
	const unsigned char *ip = reinterpret_cast<const unsigned char *>(&(address.sin_addr));
	std::sprintf(_client_ip_address, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	_locationSet = false;
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
	try
	{
		_serverName = _requestParsed.getServerName();
		_uri = _requestParsed.getUri();
		_checkRequest();
		_selectLocation();
		if (_checkRedirection())
			return ;
		_checkMethod();
		_setBody();
	} catch (const std::exception & e) {
		sendMessageToLogFile(e.what(), false, 0);
	}
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
	if ( method == "" || uri == "" || protocolVersion == "")
		_loadErrorPage("400", "Invalid request [Missing arg in request line]");
}

void	Handler::_selectLocation(void)
{
	LocationQueueType	locations;

	locations = _checkLocation();
	if (locations.empty())
		return ;
	_location = locations.top();
	_locationSet = true;
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

	_method = _requestParsed.getMethod();
	if (_locationSet == true)
	{
		methods = _location.getAllowedMethods();
		found = methods.find(_method);
		if (found == methods.end())
		{
			if (isKnownMethod(_method) == true)
				_loadErrorPage("501", "Invalid request method not implemented");
			_loadErrorPage("405", ("Method not allowed: " + _method));
		}
	}
	else if (isKnownMethod(_method) == true)
		_loadErrorPage("501", "Invalid request, method not implemented");
	if (isValidMethod(_method) == false)
		_loadErrorPage("405", ("Method not allowed: " + _method));
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
	// If a query is sent with the get request we need
	// to strip the query string ?<expression> from the uri
	std::string stripped_path;
	std::string	extension;
	Cgi			cgi;

	stripped_path = path.substr(0, path.rfind("?"));

	if (_conf.getCgi().size() == 0
			&& _location.getCgi().size() == 0)
		return(false);

	if (isDirectory(stripped_path))
	{
		checkSlash(stripped_path);
		if (findIndex(stripped_path, _location.getIndex()))
			return (false);
	} else if (!isFile(stripped_path))
		_loadErrorPage("404", "file not found [cgi]");

	extension = getExtension(stripped_path);
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
	FilesType		files;
	std::string		filePath;
	std::string		fileLocation;
	std::string		fileName;

	_checkPayload();
	if (_requestParsed.IsMultipartForm())
	{
		files = _requestParsed.getFiles();
			for (size_t i = 0; i < files.size(); i++)
			{
				fileName = files[i].fileName;
				filePath = getFilePath(_setPath(), fileName);
				fileLocation = getFileLocation(fileName, (_conf.getRoot() + _uri));
				CreateDirectory(fileName, filePath);
				response_code = CreateFile(filePath, files[i].fileContet);
				headerField = std::make_pair("Location", fileLocation);
			}
//		Response = std::make_pair(_requestParsed.getBody(), path);
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
	if (bodyLength > payloadMaxSize)
		_loadErrorPage("413", "Payload Too Large");
}

void	Handler::_loadErrorPage(std::string code, std::string message)
{
	std::string	path;

	path = _conf.getErrorPage(code);
	Response = getFileContent(path);
	response_code = code;
	if (!message.empty())
	{
		sendMessageToLogFile(message, true, 0);
		throw (std::runtime_error(message));
	}
}

void	Handler::_launchGet(std::string path)
{
	if (isDirectory(path) && _locationSet)
	{
		checkSlash(path);
		if (findIndex(path, _location.getIndex()) == true)
			Response = getFileContent(path);
		else if (_location.getAutoIndex())
			Response = getAutoIndexContent(path,
							_conf.getListen().getHost(),
							intToString(_conf.getListen().getPort()),
							_uri);
		else
			_loadErrorPage("404", "Get Failed [location]");
	}
	else if (isFile(path))
		Response = getFileContent(path);
	else
		_loadErrorPage("404", "Get Failed");
}

void	Handler::_launchDelete(std::string path)
{
	if (isDirectory(path))
		throw std::runtime_error("Delete: Invalid path: " + path);
	if (!isFile(path))
		throw std::runtime_error("Delete: path not found: " + path);
	std::remove(path.c_str());
	Response = std::make_pair(DELETE_HTML, path);
	response_code = "202";
	return ;
}

void	Handler::_launchCGI(std::string path) {
	FT::Cgi_handler cgi;
	std::map<std::string, std::string> env;

	response_code = "200";
	_prepare_env_map(env, path, _requestParsed.getBody());
	Response = std::make_pair(
			cgi.cgi_handler(response_code, env),
			path);

	if (response_code[0] > '2')
		_loadErrorPage(response_code, "CGI: Error code: " + response_code);
}

void	Handler::_prepare_env_map(std::map<std::string, std::string> &env_map,
		std::string path,
		std::string body) {

	std::string::size_type query_idx;
	std::string::size_type aux_idx;

    env_map["DOCUMENT_ROOT"] = _conf.getRoot();
    env_map["HTTP_REFERER"] = _requestParsed.getUri();
    env_map["HTTP_USER_AGENT"] = _requestParsed.getHeader("User-Agent:");

	query_idx = _uri.rfind("?");
	if (query_idx == std::string::npos || query_idx == _uri.size())
		env_map["QUERY_STRING"] = "";
	else
		env_map["QUERY_STRING"] = _uri.substr(query_idx + 1);
    env_map["REMOTE_ADDR"] = _client_ip_address;
    env_map["REMOTE_PORT"] = cast_to_string(_client_port);
    env_map["REMOTE_URI"] = _uri;

	aux_idx = _uri.rfind("/");
	if (aux_idx == std::string::npos || aux_idx == _uri.size())
		env_map["SCRIPT_NAME"] = "";
	else
		env_map["SCRIPT_NAME"] = _uri.substr(aux_idx + 1,  query_idx - aux_idx - 1);
    env_map["SCRIPT_FILENAME"] = path.substr(0, path.rfind("?"));

    env_map["SERVER_NAME"] = _serverName;
    env_map["SERVER_ADMIN"] = "I'm only a human after all, btw admin here";
    env_map["SERVER_PORT"] = cast_to_string(_conf.getListen().getPort());
	env_map["REQUEST_METHOD"] = _method;
	env_map["REQUEST_BODY"] = body;
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
