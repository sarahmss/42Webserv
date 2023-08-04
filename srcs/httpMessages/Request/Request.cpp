/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 17:26:57 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Request::Request(int clientSocket): _clientSocket(clientSocket)
{
	return ;
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
	RequestParser	Request(_clientSocket);

	_serverName = Request.getServerName();
	_uri = Request.getUri();
	_runRequest();
}

void	FT::Request::_runRequest(void)
{
	return ;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
