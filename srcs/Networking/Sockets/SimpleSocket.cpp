/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:50:43 by smodesto          #+#    #+#             */
/*   Updated: 2023/06/26 21:58:44 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/


/*
	@Defines adress structure and establish socket
	@Params
		- domain: communication domain in which the socket should be created
		- type: type of service
		- protocol: indicate a specific protocol to use in supporting the sockets operation
	htonl() converts a long integer (e.g. address) to a network representation
	htons() converts a short integer (e.g. port) to a network representation
*/
FT::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, unsigned long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	sock =  socket(domain, service, protocol);
	test_connection(sock);
}

FT::SimpleSocket::SimpleSocket( FT::SimpleSocket & src )
{
    this->address = src.address;
    this->sock = src.sock;
    this->connection = src.connection;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::SimpleSocket::~SimpleSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::SimpleSocket &				FT::SimpleSocket::operator=( FT::SimpleSocket & rhs )
{
	if ( this != &rhs )
	{
		this->address = rhs.get_address();
		this->sock = rhs.get_sock();
		this->connection = rhs.get_connection();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/


/*
	@brief: Confirms that the socket or connection has been properly established
	@param:
		item_to_test: the socket or connection
*/
void FT::SimpleSocket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{
		perror("Failed to connect");
		exit(EXIT_FAILURE);
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

struct sockaddr_in FT::SimpleSocket::get_address()
{
	return (address);
}

int FT::SimpleSocket::get_sock()
{
	return (sock);
}

int FT::SimpleSocket::get_connection()
{
	return (connection);
}

void FT::SimpleSocket::set_connection(int con)
{
	connection = con;
}
void FT::SimpleSocket::set_address(struct sockaddr_in add)
{
	address = add;
}
void FT::SimpleSocket::set_sock(int sck)
{
	sock = sck;
}
/* ************************************************************************** */
