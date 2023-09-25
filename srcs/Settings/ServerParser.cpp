/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:09:02 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/25 20:05:11 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerParser::ServerParser(){ return ; }

ServerParser::ServerParser( const ServerParser & src ){ *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerParser::~ServerParser(){ return ; }


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerParser	&ServerParser::operator=( ServerParser const & rhs )
{
	if ( this != &rhs )
	{
		this->_server = rhs.getServer();
		this->_line = rhs.getLine();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	ServerParser::launch(std::ifstream &ifstream, std::string line )
{
	_line = line;
	while(ifstream.good())
	{
		std::getline(ifstream, _line);
		if (IsValidLine(_line))
		{
			if (_line == SERVER_END)
				return ;
			if (!_line.find(LOCATION_BEGIN, 0))
				_parseLocationBlock(ifstream);
			else
				_setServer();
		}
	}
	if (_line != SERVER_END)
		throw (std::invalid_argument("Failed setting server block [missing bracket]"));
}

void	ServerParser::_parseLocationBlock(std::ifstream &ifstream)
{
	LocationParser	location;

	location.launch(ifstream, _line);
	_server.AddLocation(location.getLocation());
}

void	ServerParser::_setServer(void)
{
	if (!_line.find(LISTEN, 0))
		_checkListen();
	else if (!_line.find(SERVER_NAME, 0))
		_setServerName();
	else if (!_line.find(ROOT, 0))
		_setRoot();
	else if (!_line.find(ERROR_PAGE, 0))
		_setErrorPage();
	else if (!_line.find(CGI, 0))
		_setCgi();
	else if (!_line.find(BODY_SIZE, 0))
		_setBodySize();
	else if (_line != SERVER_END)
		throw (std::invalid_argument("Failed setting server [directives]"));
}

void	ServerParser::_checkListen(void)
{
	Listen	listen;

	ClearDirective(_line, LISTEN);
	if (_server.IsListenSet() || _line.empty() || !OnlyOneArg(_line))
		throw (std::invalid_argument("Failed setting server [listen]"));
	if (_line.find(":") == std::string::npos)
		_setPort(listen, _line);
	else
		_setListen(listen);
	_server.SetListen(listen);
}

void	ServerParser::_setListen(Listen &listen)
{
	std::stringstream	lineStream;
	std::string			host, port;

	std::getline(lineStream, host, ':');
	listen.SetHost(host);
	std::getline(lineStream, port);
	_setPort(listen, port);
}

void	ServerParser::_setPort(Listen &listen, std::string port)
{
	if (IsValidBodySize(port))
		listen.SetPort(atoi(port.c_str()));
	else
		throw (std::invalid_argument("Failed setting server [listen:port]"));
}

void	ServerParser::_setServerName(void)
{
	ClearDirective(_line, SERVER_NAME);

	if (_server.IsServerNameSet() || _line.empty())
		throw (std::invalid_argument("Failed setting server [server_name]"));
	std::stringstream	lineStream(_line);
	std::string			serverName;

	while(lineStream.good())
	{
		std::getline(lineStream, serverName, ' ');
		_server.AddServerName(serverName);
	}
}

void	ServerParser::_setBodySize(void)
{
	ClearDirective(_line, BODY_SIZE);

	if ((!IsValidBodySize(_line)) || (!OnlyOneArg(_line)) || _line.empty())
		throw (std::invalid_argument("Failed setting server [body_size] "));
	else
		_server.SetBodySize(atoi(_line.c_str()));
}

void	ServerParser::_setRoot(void)
{
	ClearDirective(_line, ROOT);

	if ((_server.IsRootSet()) || (!OnlyOneArg(_line)) || _line.empty())
		throw (std::invalid_argument("Failed setting server [root]"));
	_server.SetRoot(_line);
}


void	ServerParser::_setErrorPage(void)
{
	ClearDirective(_line, ERROR_PAGE);

	if (OnlyOneArg(_line) || _line.empty())
		throw(std::invalid_argument("Failed setting server [error_page]"));

	size_t		pos = _line.find_last_of(' ');
	std::string	pagePath = _line.substr(pos + 1);
	std::string	codes = _line.substr(0, pos);
	trim(codes, " \t");

	std::stringstream	codeStream(codes);

	while (codeStream.good())
	{
		std::getline(codeStream, codes, ' ');
		_server.AddErrorPage(codes, pagePath);
	}
}

void	ServerParser::_setCgi(void)
{
	ClearDirective(_line, CGI);

	if (_line.empty() || _line.find(":") == std::string::npos)
		throw(std::invalid_argument("Failed setting server [cgi]"));
	std::stringstream	lineStream(_line);
	std::string			extension;
	std::string			path;
	int					lineNumber = 1;

	while (lineStream.good())
	{
		switch (lineNumber)
		{
			case (1): {
				std::getline(lineStream, extension, ' ');
				break;
			}
			case (2): {
				std::getline(lineStream, path, ' ');
				break;
			}
			case (3):
				throw(std::invalid_argument("Failed setting server [cgi]"));
		}
		lineNumber += 1;
	}
	_server.AddCgi(extension, path);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

ServerConf		ServerParser::getServer(void) const
{
	return (_server);
}

std::string		ServerParser::getLine(void) const
{
	return (_line);
}

/* ************************************************************************** */
