/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:40 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::SimpleServer::SimpleServer(const int port, int backlog) : _port(port), _backlog(backlog)
{
	init();
	launch();
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

void	FT::SimpleServer::init(void)
{
	socket = new ListeningSocket(AF_INET, SOCK_STREAM, 0, _port,  INADDR_ANY, _backlog);
}


void	FT::SimpleServer::launch()
{
	while (true)
	{
		std::cout << "===== WAITING =====" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "===== DONE =====" << std::endl;
	}
}

void	FT::SimpleServer::accepter(void)
{
	ListeningSocket *	socket = get_socket();
	struct sockaddr_in	address = socket->get_address();
	int					address_len = sizeof(address);

	_newSocket = accept(socket->get_sock(), // client fd
						(struct sockaddr *)&address,
						(socklen_t *)&address_len);
}

void	FT::SimpleServer::handler(void)
{
	Request	Request(_newSocket);

	Request.launch();
}

void	FT::SimpleServer::responder(void)
{
	//std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 12\n\nHello World";
    //std::string response = resp_build.add_protocol_status("HTTP/1.1", "200");
    //response += resp_build.add_value_pair("Content_Type", "text/html");
    //response += resp_build.add_body_with_file("pages/index.html");
    resp_build.add_protocol_status("HTTP/1.1", "200");
    resp_build.add_value_pair("Content_Type", "text/html");
    resp_build.add_body_with_file("pages/index.html");
	write(_newSocket, resp_build.get_cresponse(), resp_build.get_response_size());
	close(_newSocket);
    resp_build.reset();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::ListeningSocket * FT::SimpleServer::get_socket()
{
	return (socket);
}
/* ************************************************************************** */
