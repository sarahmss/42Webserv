/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/01 23:49:16 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::WebServ::WebServ(): SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
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
	RequestParser	Request(_newSocket);
	std::cout << Request;
}

void	FT::WebServ::responder(void)
{
	std::string response = "FT/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(_newSocket, response.c_str(), response.size());
	close(_newSocket);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
