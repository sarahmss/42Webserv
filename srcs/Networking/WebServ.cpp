/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 22:57:23 by smodesto         ###   ########.fr       */
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

	bzero(&buffer, 30000);
	new_socket = accept(socket->get_sock(),
						(struct sockaddr *)&address,
						(socklen_t *)&address_len);
	read(new_socket, buffer, 30000);
}

void	FT::WebServ::handler(void)
{
	RequestParser	Request(buffer);
	std::cout << Request;
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
	write(new_socket, resp_build.get_cresponse(), resp_build.get_response_size());
	close(new_socket);
    resp_build.reset();
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
