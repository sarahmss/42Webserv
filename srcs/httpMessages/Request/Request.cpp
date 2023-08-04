/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:19:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Request::Request(int socketFd)
{
	_socketFd = socketFd;
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

	_serverName = Request.getServerName();
	_uri = Request.getUri();
	_runRequest();
}

void	FT::Request::_runRequest(void)
{
	return ;
}

void	FT::Request::_chooseServer(void)
{
	return ;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
