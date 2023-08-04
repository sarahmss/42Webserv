/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 21:54:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::WebServ::WebServ(ServerVecType confs): SimpleServer()
{
	_serversConfs = confs;
	_port = 80;
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::WebServ::~WebServ() { return ;}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	FT::WebServ::launch()
{
	init(AF_INET, SOCK_STREAM, 0, _port, INADDR_ANY, 10);
	while (true)
	{
		std::cout << "===== WAITING =====" << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "===== DONE =====" << std::endl;
	}
}

void	FT::WebServ::accepter(void)
{
	ListeningSocket *	socket = get_socket();
	struct sockaddr_in	address = socket->get_address();
	int					address_len = sizeof(address);

	_newSocket = accept(socket->get_sock(), // client fd
						(struct sockaddr *)&address,
						(socklen_t *)&address_len);
}

void	FT::WebServ::handler(void)
{
	Request	Request(_newSocket, _serversConfs);

	Request.launch();
}

void	FT::WebServ::responder(void)
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


/* ************************************************************************** */
