/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:11:47 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/10 02:11:48 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ServerConf.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ServerConf::ServerConf():			_listen(ListenType()),
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

FT::ServerConf::ServerConf( const ServerConf & src )
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ServerConf::~ServerConf() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ServerConf	&FT::ServerConf::operator=( FT::ServerConf const & rhs )
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

std::ostream &	FT::operator<<( std::ostream & o, FT::ServerConf const & i )
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

void	FT::ServerConf::AddServerName(std::string serverName)
{
	_serverName.push_back(serverName);
}

void	FT::ServerConf::AddLocation(LocationType locationBlock)
{
	_location.push_back(locationBlock);
}

void	FT::ServerConf::AddErrorPage(std::string code, std::string pagePath)
{
	_errorPages.addPage(code, pagePath);
}

void	FT::ServerConf::AddCgi(std::string extension, std::string programPath)
{
	_cgi.addProgram(extension, programPath);
}

bool	FT::ServerConf::IsListenSet(void) const
{
	return (_listen.IsSet());
}

bool	FT::ServerConf::IsServerNameSet(void) const
{
	return (!_serverName.empty());
}

bool	FT::ServerConf::IsRootSet(void) const
{
	return (!_root.empty());
}
bool	FT::ServerConf::IsErrorPageSet(std::string code) const
{
	return (_errorPages.hasPage(code));
}

std::string		FT::ServerConf::ServerNameToString(void) const
{
	std::string	FinalStr;

	for (size_t i = 0; i < _serverName.size(); i++)
		FinalStr += _serverName[i] + " ";
	return (FinalStr);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
ListenType	FT::ServerConf::getListen(void) const
{
	return (_listen);
}
ServerNameType	FT::ServerConf::getServerName(void) const
{
	return (_serverName);
}
std::string	FT::ServerConf::getRoot(void) const
{
	return (_root);
}
std::string	FT::ServerConf::getErrorPage(std::string code) const
{
	return (_errorPages.getErrorPage(code));
}
ErrorType	FT::ServerConf::getDefaultErrorPages(void) const
{
	return (_errorPagesDefault);
}
ErrorType	FT::ServerConf::getErrorPages(void) const
{
	return (_errorPages);
}

CgiType		FT::ServerConf::getCgi(void) const
{
	return (_cgi);
}
int			FT::ServerConf::getBodySize(void) const
{
	return (_bodySize);
}
LocationVecType	FT::ServerConf::getLocation(void) const
{
	return (_location);
}

void	FT::ServerConf::SetListen(ListenType listen)
{
	_listen = listen;
}

void	FT::ServerConf::SetRoot(std::string root)
{
	_root = root;
}

void	FT::ServerConf::SetBodySize(int bodySize)
{
	_bodySize = bodySize;
}


/* ************************************************************************** */
