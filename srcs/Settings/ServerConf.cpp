/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:11:47 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/23 19:52:47 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ServerConf.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf():			_listen(ListenType()),
								_serverName(ServerNameType()),
								_location(LocationVecType()),
								_errorPages(ErrorType()),
								_errorPagesDefault(ErrorType()),
								_cgi(CgiType()),
								_root(""),
								_bodySize(1000000) //1MB
{
	_errorPages.SetDefaultPages();
	return ;
}

ServerConf::ServerConf( const ServerConf & src )
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerConf::~ServerConf() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerConf	&ServerConf::operator=( ServerConf const & rhs )
{
	if ( this != &rhs )
	{
		this->_listen = rhs.getListen();
		this->_serverName = rhs.getServerName();
		this->_root = rhs.getRoot();
		this->_errorPages = rhs.getErrorPages();
		this->_errorPagesDefault = getDefaultErrorPages();
		this->_cgi = rhs.getCgi();
		this->_bodySize = rhs.getBodySize();
		this->_location =  rhs.getLocation();
	}
	return *this;
}

std::ostream &	operator<<( std::ostream & o, ServerConf const & i )
{
	o	<< "Listen: "				<< i.getListen()			<< std::endl
		<< "Server Name: "			<< i.ServerNameToString()	<< std::endl
		<< "Root: " 				<< i.getRoot()				<< std::endl
		<< "Error Pages: " 			<< i.getErrorPages()		<< std::endl
		<< "Error Pages Default: "	<< i.getDefaultErrorPages()	<< std::endl
		<< "Cgi: " 					<< i.getCgi()				<< std::endl
		<< "Body Size: "			<< i.getBodySize()			<< std::endl
		<< "Location: "				<<	std::endl;
		for (size_t j=0; j < i.getLocation().size(); j++)
			o << i.getLocation()[j] << std::endl;

	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	ServerConf::AddServerName(std::string serverName)
{
	_serverName.push_back(serverName);
}

void	ServerConf::AddLocation(LocationType locationBlock)
{
	_location.push_back(locationBlock);
}

void	ServerConf::AddErrorPage(std::string code, std::string pagePath)
{
	_errorPages.addPage(code, pagePath);
}

void	ServerConf::AddCgi(std::string extension, std::string programPath)
{
	_cgi.addProgram(extension, programPath);
}

bool	ServerConf::IsListenSet(void) const
{
	return (_listen.IsSet());
}

bool	ServerConf::IsServerNameSet(void) const
{
	return (!_serverName.empty());
}

bool	ServerConf::IsRootSet(void) const
{
	return (!_root.empty());
}
bool	ServerConf::IsErrorPageSet(std::string code) const
{
	return (_errorPages.hasPage(code));
}

std::string		ServerConf::ServerNameToString(void) const
{
	std::string	FinalStr;

	for (size_t i = 0; i < _serverName.size(); i++)
		FinalStr += _serverName[i] + " ";
	return (FinalStr);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
ListenType	ServerConf::getListen(void) const
{
	return (_listen);
}
ServerNameType	ServerConf::getServerName(void) const
{
	return (_serverName);
}
std::string	ServerConf::getRoot(void) const
{
	return (_root);
}
std::string	ServerConf::getErrorPage(std::string code) const
{
	return (_errorPages.getErrorPage(code));
}
ErrorType	ServerConf::getDefaultErrorPages(void) const
{
	return (_errorPagesDefault);
}
ErrorType	ServerConf::getErrorPages(void) const
{
	return (_errorPages);
}

CgiType		ServerConf::getCgi(void) const
{
	return (_cgi);
}
int			ServerConf::getBodySize(void) const
{
	return (_bodySize);
}
LocationVecType	ServerConf::getLocation(void) const
{
	return (_location);
}

void	ServerConf::SetListen(ListenType listen)
{
	_listen = listen;
}

void	ServerConf::SetRoot(std::string root)
{
	_root = root;
}

void	ServerConf::SetBodySize(int bodySize)
{
	_bodySize = bodySize;
}


/* ************************************************************************** */
