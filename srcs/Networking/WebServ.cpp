/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/07 17:07:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"
#include <sys/epoll.h>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::WebServ::WebServ(ServerVecType confs):
									_epoll(MAX_EVENTS * confs.size()),
									_serversConfs(confs),
									_backLog(50)
{
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::WebServ::~WebServ(void) {
	for (size_t i = 0; i < _simpleServers.size(); i++)
		if (_simpleServers[i])
			delete _simpleServers[i];
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	FT::WebServ::launch(void)
{
	_groupServers();
	_initServers();
	_coreLoop();
}

/*
	@brief: Group Servers defined in conf file by ports number
*/
void	FT::WebServ::_groupServers(void)
{
	for (size_t i = 0; i < _serversConfs.size(); i++)
	{
		int port = _serversConfs[i].getListen().getPort();
		_portServer[port].push_back(_serversConfs[i]);
	}
}

/*
	@brief: Init Servers based in port number
*/
void	FT::WebServ::_initServers(void)
{
	PortServerType::iterator	begin = _portServer.begin();
	PortServerType::iterator	end = _portServer.end();

	for (int i  = 0; begin != end; begin++, i++)
	{
		SimpleServer	*newServer = new SimpleServer(begin->first, _backLog);
		_addToPoll(newServer);
		_simpleServers.push_back(newServer);
	}
}

/*
	@brief: add server to PollHandler to manage read/write events
*/
void	FT::WebServ::_addToPoll(SimpleServer *newServer)
{
	_epoll.add(newServer->getSocket(), _epoll.ServerToData(newServer), 	EPOLLIN | EPOLLOUT);
}

void	FT::WebServ::_removeFromPoll(int fd)
{
	_epoll.remove(fd);
	close(fd);
}

/*
	@brief: Waits for I/O events
*/
void	FT::WebServ::_coreLoop(void)
{
	SimpleServer	*server;
	int				numEvents;

	while (true)
	{
		numEvents = _epoll.wait(0);
		for (int i = 0; i < numEvents; i++)
		{
			epollEventType	&currentEvent = _epoll.getEvents()[i];
			server = static_cast<SimpleServer *>(currentEvent.data.ptr);

			_accepter(server);
			if (currentEvent.events & EPOLLIN)
				_responder(server);
			if (currentEvent.events & EPOLLOUT)
				_handler(server);
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
void	FT::WebServ::_accepter(SimpleServer* server)
{
	ListeningSocket *	socket = server->getListeningSocket();
	struct sockaddr_in	address = socket->get_address();
	int					address_len = sizeof(address);
	int					clientSocket;

	clientSocket = accept(socket->get_sock(),
						(struct sockaddr *)&address,
						(socklen_t *)&address_len);
	_epoll.add(clientSocket, _epoll.ServerToData(server), EPOLLIN | EPOLLOUT);
	server->setClientSocket(clientSocket);
}
void	FT::WebServ::_handler(SimpleServer* server)
{
	int		clientSocket = server->getClientSocket();
	Request	Request(clientSocket);

	Request.launch();
	std::cout << Request.getRequestParser();
	_epoll.modify(clientSocket, _epoll.ServerToData(server), EPOLLOUT);
}

void	FT::WebServ::_responder(SimpleServer* server)
{
	int clientSocket = server->getClientSocket();

	resp_build.add_protocol_status("HTTP/1.1", "200");
	resp_build.add_value_pair("Content_Type", "text/html");
	resp_build.add_body_with_file("pages/index.html");

	if (send(clientSocket, resp_build.get_cresponse(), resp_build.get_response_size(), 0) < 0)
		throw std::runtime_error("Error sending response");
	_removeFromPoll(clientSocket);
	resp_build.reset();
}


/* ************************************************************************** */
