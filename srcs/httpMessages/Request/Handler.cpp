/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/23 13:21:17 by smodesto         ###   ########.fr       */
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
	try
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
	catch (const std::exception & e)
	{
		sendMessageToLogFile(e.what(), false, 0);
		return ;
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
		_launchPost(path);
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

	if (_conf.getCgi().size() == 0
			&& _location.getCgi().size() == 0)
		return(false);

	if (isDirectory(path))
	{
		checkSlash(path);
		if (findIndex(path, _location.getIndex()))
			return (false);
	} else if (!isFile(path))
	{
		sendMessageToLogFile("404 | checkCGI->Handler", false, 0);
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

void	Handler::checkDirNSendBySocket( void )
{
	const char *diretorio = "/root/webserv/upload/www/backend";

    DIR *dir;
    struct dirent *ent;
	std::ostringstream response;

	if ((dir = opendir(diretorio)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type == DT_REG)
			{
				response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
							 				<< strlen(ent->d_name) << "\r\n\r\n";
				response << ent->d_name;
				send(_clientSocket, response.str().c_str(), response.str().length(), 0);
				std::cout << "Arquivo: " << ent->d_name << std::endl;
			}
		}
	closedir(dir);
    }
	else
	{
        perror("Erro ao abrir diretório");
        return ;
    }

}

void	Handler::_launchPost(std::string path)
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
		Response = std::make_pair(_requestParsed.getBody(), path);
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
			Response = getFileContent(path);
		else if (_location.getAutoIndex())
			Response = getAutoIndexContent(path,
							_conf.getListen().getHost(),
							intToString(_conf.getListen().getPort()),
							_uri);
		else
			response_code = "404";
	}
	else if (isFile(path))
		Response = getFileContent(path);
	else
	{
		response_code = "404";
		path = _conf.getErrorPage("404");
		Response = getFileContent(path);
	}
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
	_prepare_env_map(env, path);
	Response = std::make_pair(
			cgi.cgi_handler(response_code, env, _requestParsed.getBody()),
			path);
}

void	Handler::_prepare_env_map(std::map<std::string, std::string> &env_map, std::string path) {
	std::string::size_type aux_idx;

    env_map["DOCUMENT_ROOT"] = _conf.getRoot();
    env_map["HTTP_REFERER"] = _requestParsed.getUri();
    env_map["HTTP_USER_AGENT"] = _requestParsed.getHeader("User-Agent:");

	aux_idx = _uri.rfind("?");
	if (aux_idx == std::string::npos || aux_idx == _uri.size())
		env_map["QUERY_STRING"] = "";
	else
		env_map["QUERY_STRING"] = _uri.substr(aux_idx + 1);

    env_map["REMOTE_ADDR"] = _client_ip_address;
    env_map["REMOTE_PORT"] = cast_to_string(_client_port);
    env_map["REMOTE_URI"] = _uri;

	aux_idx = _uri.rfind("/");
	if (aux_idx == std::string::npos || aux_idx == _uri.size())
		env_map["SCRIPT_NAME"] = "";
	else
		env_map["SCRIPT_NAME"] = _uri.substr(aux_idx + 1);
    env_map["SCRIPT_FILENAME"] = path;

    env_map["SERVER_NAME"] = _serverName;
    env_map["SERVER_ADMIN"] = "I'm only a human after all, btw admin here";
    env_map["SERVER_PORT"] = cast_to_string(_conf.getListen().getPort());

	env_map["REQUEST_METHOD"] = _method;
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
