/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 21:56:57 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Request::Request(int socketFd, ServerVecType confs)
{
	_socketFd = socketFd;
	_serversConfs = confs;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Request::~Request() { return ;}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/
void	FT::Request::launch(void)
{
	RequestParser	Request(_socketFd);

	_serverName = Request.GetServerName();
	_uri = Request.GetUri();
	_runRequest();
}

void	FT::Request::_runRequest(void)
{
	/*	_chooseServer();*/
	return ;
}

void	FT::Request::_chooseServer(void)
{
/*	ServerVecType::iterator begin = _serversConfs.begin();
	ServerVecType::iterator end = _serversConfs.end();

	for (; begin != end; begin++)
	{

	}
*/
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
