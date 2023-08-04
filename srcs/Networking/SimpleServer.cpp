/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:40 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 18:25:49 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::SimpleServer::SimpleServer(const int port, int backlog) : _port(port), _backlog(backlog)
{
	init();
	return ;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::SimpleServer::~SimpleServer()
{
	delete socket;
	return ;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

/*
	@brief: Creates a new instance of ListeningSocket to create a socket wich is able to accept connections
*/
void	FT::SimpleServer::init(void)
{
	socket = new ListeningSocket(AF_INET, SOCK_STREAM, 0, _port,  INADDR_ANY, _backlog);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::ListeningSocket * FT::SimpleServer::getListeningSocket(void)
{
	return (socket);
}

int	FT::SimpleServer::getSocket(void)
{
	return (getListeningSocket()->get_sock());
}

int	FT::SimpleServer::getClientSocket(void)
{
	return (_clientSocket);
}

void	FT::SimpleServer::setClientSocket(int clientSocket)
{
	_clientSocket = clientSocket;
}

int	FT::SimpleServer::getPort(void)
{
	return (_port);
}

int	FT::SimpleServer::getBacklog(void)
{
	return (_backlog);
}

/* ************************************************************************** */
