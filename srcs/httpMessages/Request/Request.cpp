/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:25 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 18:57:25 by smodesto         ###   ########.fr       */
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
	_requestParsed = RequestParser(_clientSocket);

	_serverName = _requestParsed.getServerName();
	_uri = _requestParsed.getUri();
	_runRequest();
}

void	FT::Request::_runRequest(void)
{
	return ;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::RequestParser	FT::Request::getRequestParser(void)
{
	return (_requestParsed);
}
/* ************************************************************************** */
