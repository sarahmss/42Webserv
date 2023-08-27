/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/24 00:58:51 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"
#include <netinet/in.h>
#include <sys/epoll.h>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

WebServ::WebServ(ConfsVecType confs):
									_epoll(MAX_EVENTS * confs.size()),
									_serversConfs(confs),
									_backLog(50)
{
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

WebServ::~WebServ(void) {
	for (size_t i = 0; i < _simpleServers.size(); i++)
		if (_simpleServers[i])
			delete _simpleServers[i];
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	WebServ::launch(void)
{
	_initServers();
	_coreLoop();
}

/*
	@brief: Init Servers based in port number
*/
void	WebServ::_initServers(void)
{
	// [LOGGING]
	std::cout << "++ Initing Servers" << std::endl;
	for (size_t i = 0; i < _serversConfs.size(); i++)
	{
		int port = _serversConfs[i].getListen().getPort();
		// [LOGGING]
		std::cout << "++ Starting listen() in port " << port << std::endl;
		SimpleServer	*newServer = new SimpleServer(_serversConfs[i],
														port,
														_backLog);
		_addToPoll(newServer);
		_simpleServers.push_back(newServer);
	}
}

/*
	@brief: add server to PollHandler to manage read/write events
*/
void	WebServ::_addToPoll(SimpleServer *newServer)
{
	_epoll.add(newServer->getSocket(), _epoll.ServerToData(newServer), 	EPOLLIN | EPOLLOUT);
}

void	WebServ::_removeFromPoll(int fd)
{
	_epoll.remove(fd);
	close(fd);
}

/*
	@brief: Waits for I/O events
*/
void	WebServ::_coreLoop(void)
{
	SimpleServer		*server;
	int					numEvents;
	struct sockaddr_in	client_addr;

	while (true)
	{
		numEvents = _epoll.wait(0);
		for (int i = 0; i < numEvents; i++)
		{
			epollEventType	&currentEvent = _epoll.getEvents()[i];
			server = static_cast<SimpleServer *>(currentEvent.data.ptr);

			if (currentEvent.events & EPOLLIN)
			{
				_launchAccepter(server, client_addr);
				_launchHandler(server, client_addr);
			}
			if (currentEvent.events & EPOLLOUT)
				_launchResponder(server);
			if (currentEvent.events & EPOLLERR)
			{
				_removeFromPoll(server->getClientSocket());
				throw (std::runtime_error("Epoll error"));
			}
			if (currentEvent.events & (EPOLLRDHUP | EPOLLHUP))
				_removeFromPoll(server->getClientSocket());
		}
	}
}

/*
	@brief: accepts an incoming connection and creates a client socket
	which represents accepted connection
*/
void	WebServ::_launchAccepter(SimpleServer *server, struct sockaddr_in &address)
{
	ListeningSocket *	socket = server->getListeningSocket();
	int					address_len = sizeof(address);
	int					clientSocket;

	address = socket->get_address();

	// [LOGGING]
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cout << "++ Accepting conections in " << server->getPort() << std::endl;

	clientSocket = accept(socket->get_sock(),
						(struct sockaddr *)&address,
						(socklen_t *)&address_len);

	_epoll.add(clientSocket, _epoll.ServerToData(server), EPOLLIN | EPOLLOUT);
	server->setClientSocket(clientSocket);
}

void	WebServ::_launchHandler(SimpleServer *server, struct sockaddr_in &address)
{
	int			clientSocket = server->getClientSocket();
	_handler = Handler(clientSocket, server->getConf(), address);

	// [LOGGING]
	std::cout << "++ Request Received " << std::endl;
	_handler.launch();
	_epoll.modify(clientSocket, _epoll.ServerToData(server), EPOLLOUT);
}

void	WebServ::_launchResponder(SimpleServer* server)
{
	int	clientSocket = server->getClientSocket();

	// [LOGGING]
	std::cout << " ++ launching responder" << std::endl;
	_responder.launch(clientSocket,
			server->getConf().ServerNameToString(),
			_handler.response_code,
			_handler.getResponsePath.first,
			_handler.headerField);
	try
	{
		_responder.sendResponse();
		// [LOGGING]
		std::cout << "++ Response sent " << std::endl;
	}
	catch (const std::exception & e)
	{
		return ;
		// [LOGGING] response failed
	}
	_removeFromPoll(clientSocket);
}


/* ************************************************************************** */
