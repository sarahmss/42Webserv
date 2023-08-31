/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/31 19:58:43 by smodesto         ###   ########.fr       */
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
	for (size_t i = 0; i < _serversConfs.size(); i++)
	{
		if (_simpleServers[i])
			delete _simpleServers[i];
		if (_serverChannels[i])
			delete _serverChannels[i];
	}
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
		std::cout << "++ Starting listen() in port " << intToString(port) << std::endl;
		SimpleServer	*newServer = new SimpleServer(_serversConfs[i],
														port,
														_backLog);
		_simpleServers.push_back(newServer);
		_addServerToPoll(newServer);
	}
}

/*
	@brief: add server to PollHandler to manage read/write events
*/
void	WebServ::_addServerToPoll(SimpleServer *newServer)
{
	t_channel	*channel = new t_channel;

	channel->type = t_channel::CHANNEL_SOCKET;
	channel->ptr = newServer;

	_epoll.add(newServer->getSocket(),
				_epoll.ChannelToData(channel),
				EPOLLIN | EPOLLOUT);
	_serverChannels.push_back(channel);
}

void	WebServ::_addConnectionsToPoll(AcceptingSocket *acc, SimpleServer *serv)
{
	t_channel		*channel = new t_channel;
	ConnectionType	*data;

	data = new ConnectionType(acc, serv);
	channel->type = t_channel::CHANNEL_CONNECTION;
	channel->ptr = data;

	_epoll.add(acc->getClientSocket(),
				_epoll.ChannelToData(channel),
				EPOLLIN);
}

void	WebServ::_removeConnectionFromPoll(ConnectionType *cnc, t_channel *chnl)
{
	AcceptingSocket		*accepter = cnc->first;

	_epoll.remove(accepter->getClientSocket());
	accepter->disconnect();
	delete accepter;
	delete cnc;
	delete chnl;
}

/*
	@brief: Waits for I/O events
*/
void	WebServ::_coreLoop(void)
{
	t_channel			*channel;
	SimpleServer		*server;
	AcceptingSocket		*accepter;
	ConnectionType		*connection;
	int					numEvents;

	std::signal(SIGINT, sigHandler);
	std::signal(SIGQUIT, sigHandler);

	while (live(true))
	{
		numEvents = _epoll.wait(0);
		if (numEvents == -1)
			live(false);
		for (int i = 0; i < numEvents; i++)
		{
			epollEventType	&currentEvent = _epoll.getEvents()[i];
			channel = reinterpret_cast<t_channel *>(currentEvent.data.ptr);

			if (channel->type == t_channel::CHANNEL_SOCKET)
			{
				server = reinterpret_cast<SimpleServer *>(channel->ptr);
				_launchAccepter(server);
			}
			else if (channel->type == t_channel::CHANNEL_CONNECTION)
			{
				connection = reinterpret_cast<ConnectionType *>(channel->ptr);
				if (currentEvent.events & EPOLLERR)
					_removeConnectionFromPoll(connection, channel); // [LOGGING]
				if (currentEvent.events & (EPOLLRDHUP | EPOLLHUP))
					_removeConnectionFromPoll(connection, channel);

				accepter = connection->first;
				server = connection->second;

				if (currentEvent.events & EPOLLIN)
				{
					_launchHandler(server, accepter);
					_epoll.modify(accepter->getClientSocket(),
									_epoll.ChannelToData(channel),
									EPOLLOUT);
				}
				if (currentEvent.events & EPOLLOUT)
				{
					_launchResponder(server, accepter);
					_removeConnectionFromPoll(connection, channel);
				}
			}
		}
	}
}

/*
	@brief: accepts an incoming connection and creates a client socket
	which represents accepted connection
*/
void	WebServ::_launchAccepter(SimpleServer *server)
{
	AcceptingSocket	*accepter =  new AcceptingSocket();
	int				serverSocket = server->getSocket();
	int				connectionSocket;

	connectionSocket = accepter->startAccepting(serverSocket);
	std::cout << "++ Connection opened in socket: " + intToString( connectionSocket) << std::endl;
	_addConnectionsToPoll(accepter, server);
}

void	WebServ::_launchHandler(SimpleServer *server, AcceptingSocket *accept)
{
	int			clientSocket = accept->getClientSocket();
	sockaddr_in	address = accept->getClientAddress();

	_handler = Handler(clientSocket, server->getConf(), address);

	// [LOGGING]
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "++ Request Received " << std::endl;
	_handler.launch();
}

void	WebServ::_launchResponder(SimpleServer *server, AcceptingSocket *accept)
{
	int	clientSocket = accept->getClientSocket();

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
}


/* ************************************************************************** */
