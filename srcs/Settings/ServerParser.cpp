/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:09:02 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/20 17:10:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ServerParser::ServerParser(){ return ; }

FT::ServerParser::ServerParser( const ServerParser & src ){ *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ServerParser::~ServerParser(){ return ; }


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ServerParser	&FT::ServerParser::operator=( ServerParser const & rhs )
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

void	FT::ServerParser::exec(std::ifstream &ifstream, std::string line )
{
	_line = line;
	while(ifstream.good())
	{
		std::getline(ifstream, _line);
		if (FT::IsValidLine(_line))
		{
			if (_line == SERVER_END)
				return ;
			if (!_line.find(LOCATION_BEGIN, 0))
				_parseLocationBlock(ifstream);
			else
				_setServer();
		}
	}
}

void	FT::ServerParser::_parseLocationBlock(std::ifstream &ifstream)
{
	FT::LocationParser	location;

	location.exec(ifstream, _line);
	_server.AddLocation(location.getLocation());
}

void	FT::ServerParser::_setServer(void)
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
	else
		throw (std::invalid_argument("Failed setting server [directives]"));
}

void	FT::ServerParser::_checkListen(void)
{
	FT::Listen	listen;

	FT::ClearDirective(_line, LISTEN);
	if (_server.IsListenSet() || _line.empty() || !OnlyOneArg(_line))
		throw (std::invalid_argument("Failed setting server [listen]"));
	if (_line.find(":") == std::string::npos)
		_setPort(listen, _line);
	else
		_setListen(listen);
	_server.SetListen(listen);
}

void	FT::ServerParser::_setListen(Listen &listen)
{
	std::stringstream	lineStream;
	std::string			host, port;

	std::getline(lineStream, host, ':');
	listen.SetHost(host);
	std::getline(lineStream, port);
	_setPort(listen, port);
}

void	FT::ServerParser::_setPort(Listen &listen, std::string port)
{
	if (FT::IsNumber(port))
		listen.SetPort(atoi(port.c_str()));
	else
		throw (std::invalid_argument("Failed setting server [listen:port]"));
}

void	FT::ServerParser::_setServerName(void)
{
	FT::ClearDirective(_line, SERVER_NAME);

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

void	FT::ServerParser::_setBodySize(void)
{
	FT::ClearDirective(_line, BODY_SIZE);

	if ((!FT::IsNumber(_line)) || (!FT::OnlyOneArg(_line)) || _line.empty())
		throw (std::invalid_argument("Failed setting server [body_size] "));
	else
		_server.SetBodySize(atoi(_line.c_str()));
}

void	FT::ServerParser::_setRoot(void)
{
	FT::ClearDirective(_line, ROOT);

	if ((_server.IsRootSet()) || (!FT::OnlyOneArg(_line)) || _line.empty())
		throw (std::invalid_argument("Failed setting server [redirection]"));
	_server.SetRoot(_line);
}


void	FT::ServerParser::_setErrorPage(void)
{
	FT::ClearDirective(_line, ERROR_PAGE);

	if (FT::OnlyOneArg(_line))
		throw(std::invalid_argument("Failed setting server [error_page]"));

	size_t		pos = _line.find_last_of(' ');
	std::string	pagePath = _line.substr(pos + 1);
	std::string	codes = _line.substr(0, pos);
	FT::trim(codes, " \t");

	std::stringstream	codeStream(codes);

	while (codeStream.good())
	{
		std::getline(codeStream, codes, ' ');
		_server.AddErrorPage(codes, pagePath);
	}
}

void	FT::ServerParser::_setCgi(void)
{
	FT::ClearDirective(_line, CGI);

	if (OnlyOneArg(_line))
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
				throw(std::invalid_argument("Failed setting location [cgi]"));
		}
		lineNumber += 1;
	}
	_server.AddCgi(extension, path);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::Server		FT::ServerParser::getServer(void) const
{
	return (_server);
}

std::string		FT::ServerParser::getLine(void) const
{
	return (_line);
}

/* ************************************************************************** */
