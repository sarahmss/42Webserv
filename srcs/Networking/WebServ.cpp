/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/30 21:37:50 by jinacio-         ###   ########.fr       */
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

std::string		WebServ::concatenate_string(std::string s1, std::string s2)
{
	std::string ret = s1 + s2;
	return ret;
}

std::string		WebServ::concatenate_int(std::string s1, int n2)
{
	std::ostringstream oss;
    oss << n2;
    
    std::string resultado = s1 + oss.str();
    return resultado;
}

void	WebServ::_initServers(void)
{
	
	sendMessageToLogFile("Initing Server...", true, 0);
	clock_t start = clock();
	clock_t end = clock();
	std::cout << "++ Initing Servers" << std::endl;
	for (size_t i = 0; i < _serversConfs.size(); i++)
	{
		start = clock();
		int port = _serversConfs[i].getListen().getPort();
		sendMessageToLogFile(concatenate_int("Starting listen() int port ", port), true, 
										static_cast<double>(end - start) / CLOCKS_PER_SEC);
		std::cout << "++ Starting listen() in port " << port << std::endl;
		SimpleServer	*newServer = new SimpleServer(_serversConfs[i],
														port,
														_backLog);
		_addToPoll(newServer);
		_simpleServers.push_back(newServer);
		end = clock();
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

	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cout << "++ Accepting connections in " << server->getPort() << std::endl;
	sendMessageToLogFile(concatenate_int("Accepting connections in ", server->getPort()), true, 0);

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

	sendMessageToLogFile("Request Received", true, 0);
	std::cout << "++ Request Received " << std::endl;
	_handler.launch();
	_epoll.modify(clientSocket, _epoll.ServerToData(server), EPOLLOUT);
}

void	WebServ::_launchResponder(SimpleServer* server)
{
	int	clientSocket = server->getClientSocket();

	sendMessageToLogFile("Launching responder", true, 0);
	std::cout << " ++ launching responder" << std::endl;
	_responder.launch(clientSocket,
			server->getConf().ServerNameToString(),
			_handler.response_code,
			_handler.getResponsePath.first,
			_handler.headerField);
	try
	{
		_responder.sendResponse();
		sendMessageToLogFile("Response sent ", true, 0);
		std::cout << "++ Response sent " << std::endl;
	}
	catch (const std::exception & e)
	{
		sendMessageToLogFile(e.what(), false, 0);
		return ;
	}
	_removeFromPoll(clientSocket);
}


/* ************************************************************************** */
