/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/23 15:28:42 by smodesto         ###   ########.fr       */
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

	sendMessageToLogFile("++ Initing Server...", true, 0);
	clock_t start = clock();
	clock_t end = clock();
	std::cout << "++ Initing Servers" << std::endl;
	for (size_t i = 0; i < _serversConfs.size(); i++)
	{
		start = clock();
		int port = _serversConfs[i].getListen().getPort();

		sendMessageToLogFile(concatenate_int("++ Starting listen() int port ", port), true,
										static_cast<double>(end - start) / CLOCKS_PER_SEC);
		std::cout << "++ Starting listen() in port " << intToString(port) << std::endl; // debug level
		SimpleServer	*newServer = new SimpleServer(_serversConfs[i],
														port,
														_backLog);
		_simpleServers.push_back(newServer);
		_addServerToPoll(newServer);
    end = clock();
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
					_removeConnectionFromPoll(connection, channel);
				if (currentEvent.events & (EPOLLRDHUP | EPOLLHUP))
					_removeConnectionFromPoll(connection, channel);

				accepter = connection->first;
				server = connection->second;

				if (currentEvent.events & EPOLLIN)
				{
					try {
						_launchHandler(server, accepter);
						_epoll.modify(accepter->getClientSocket(),
									_epoll.ChannelToData(channel), EPOLLOUT);
					} catch (const std::exception & e) {
						std::cout << e.what() << std::endl;
						sendMessageToLogFile(e.what(), false, 0);
						_removeConnectionFromPoll(connection, channel);
					}
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
	std::cout << "++ Connection opened in socket: " + intToString( connectionSocket) << std::endl; // debug level
  sendMessageToLogFile(concatenate_int("++ Connection opened in socket: ", connectionSocket), true, 0);
	_addConnectionsToPoll(accepter, server);
}

void	WebServ::_launchHandler(SimpleServer *server, AcceptingSocket *accept)
{
	int			clientSocket = accept->getClientSocket();
	sockaddr_in	address = accept->getClientAddress();

	sendMessageToLogFile("++ Request Received", true, 0);
	_handler = Handler(clientSocket, server->getConf(), address);
	_handler.launch();
}

void	WebServ::_launchResponder(SimpleServer *server, AcceptingSocket *accept)
{
	int	clientSocket = accept->getClientSocket();

	sendMessageToLogFile("++ Launching responder", true, 0);
	_responder.launch(clientSocket,
			server->getConf().ServerNameToString(),
			_handler.response_code,
			_handler.Response.first,
			_handler.headerField);
	try {
		_responder.sendResponse();
		sendMessageToLogFile("++ Response sent ", true, 0);
	} catch (const std::exception & e) {
		sendMessageToLogFile(e.what(), false, 0);
		return ;
	}
}


/* ************************************************************************** */
