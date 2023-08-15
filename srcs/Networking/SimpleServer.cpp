/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:40 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

SimpleServer::SimpleServer(ServerConf confs, const int port, int backlog) :
								_confs(confs),
								_port(port),
								_backlog(backlog)
{
	init();
	return ;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

SimpleServer::~SimpleServer()
{
	close(getSocket());
	delete socket;
	return ;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

/*
	@brief: Creates a new instance of ListeningSocket to create a socket wich is able to accept connections
*/
void	SimpleServer::init(void)
{
	socket = new ListeningSocket(AF_INET, SOCK_STREAM, 0, _port,  INADDR_ANY, _backlog);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

ListeningSocket	*SimpleServer::getListeningSocket(void)
{
	return (socket);
}

ServerConf	SimpleServer::getConf(void)
{
	return (_confs);
}

int	SimpleServer::getSocket(void)
{
	return (getListeningSocket()->get_sock());
}

int	SimpleServer::getClientSocket(void)
{
	return (_clientSocket);
}

void	SimpleServer::setClientSocket(int clientSocket)
{
	_clientSocket = clientSocket;
}

int	SimpleServer::getPort(void)
{
	return (_port);
}

int	SimpleServer::getBacklog(void)
{
	return (_backlog);
}

/* ************************************************************************** */
