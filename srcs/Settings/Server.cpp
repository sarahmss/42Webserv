/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInf<< " " << i.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:15:28 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/10 21:36:35 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Server::Server():			_listen(ListenType()),
								_serverName(ServerNameType()),
								_location(LocationVecType()),
								_errorPages(ErrorType()),
								_errorPagesDefault(ErrorType()),
								_cgi(CgiType()),
								_root(""),
								_bodySize(1000000)
{
	_errorPages.SetDefaultPages();
	return ;
}

FT::Server::Server( const Server & src )
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Server::~Server() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::Server	&FT::Server::operator=( FT::Server const & rhs )
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

std::ostream &	FT::operator<<( std::ostream & o, FT::Server const & i )
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

void	FT::Server::AddServerName(std::string serverName)
{
	_serverName.push_back(serverName);
}

void	FT::Server::AddLocation(LocationType locationBlock)
{
	_location.push_back(locationBlock);
}

void	FT::Server::AddErrorPage(std::string code, std::string pagePath)
{
	_errorPages.addPage(code, pagePath);
}

void	FT::Server::AddCgi(std::string extension, std::string programPath)
{
	_cgi.addProgram(extension, programPath);
}

bool	FT::Server::IsListenSet(void) const
{
	return (_listen.IsSet());
}

bool	FT::Server::IsServerNameSet(void) const
{
	return (!_serverName.empty());
}

bool	FT::Server::IsRootSet(void) const
{
	return (!_root.empty());
}
bool	FT::Server::IsErrorPageSet(std::string code) const
{
	return (_errorPages.hasPage(code));
}

std::string		FT::Server::ServerNameToString(void) const
{
	std::string	FinalStr;

	for (size_t i = 0; i < _serverName.size(); i++)
		FinalStr += _serverName[i] + " ";
	return (FinalStr);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
ListenType	FT::Server::getListen(void) const
{
	return (_listen);
}
ServerNameType	FT::Server::getServerName(void) const
{
	return (_serverName);
}
std::string	FT::Server::getRoot(void) const
{
	return (_root);
}
std::string	FT::Server::getErrorPage(std::string code) const
{
	return (_errorPages.getErrorPage(code));
}
ErrorType	FT::Server::getDefaultErrorPages(void) const
{
	return (_errorPagesDefault);
}
ErrorType	FT::Server::getErrorPages(void) const
{
	return (_errorPages);
}

CgiType		FT::Server::getCgi(void) const
{
	return (_cgi);
}
int			FT::Server::getBodySize(void) const
{
	return (_bodySize);
}
LocationVecType	FT::Server::getLocation(void) const
{
	return (_location);
}

void	FT::Server::SetListen(ListenType listen)
{
	_listen = listen;
}

void	FT::Server::SetRoot(std::string root)
{
	_root = root;
}

void	FT::Server::SetBodySize(int bodySize)
{
	_bodySize = bodySize;
}


/* ************************************************************************** */
