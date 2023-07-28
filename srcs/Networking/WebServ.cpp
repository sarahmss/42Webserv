/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/22 19:42:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <cerrno>

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
    return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
  throw(errno);
}

std::string cast_to_string(int num) {
    std::ostringstream out_stream;
    out_stream << num;
    return (out_stream.str());
}

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
	std::cout << buffer << std::endl;
}

void	FT::WebServ::responder(void)
{
	std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    std::string buff_response = get_file_contents("pages/std.html");
    response += cast_to_string(buff_response.size()) + "\n\n";
    response += buff_response;

	write(new_socket, response.c_str(), response.size());
	close(new_socket);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
