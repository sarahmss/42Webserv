/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:44 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/01 22:21:21 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindingSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BindingSocket::BindingSocket(int domain, int service, int protocol, int port, unsigned long interface):
	SimpleSocket(domain, service, protocol, port, interface)
{
	int			optval = 1;
	int			sock = get_sock();
	sockaddr_in	address = get_address();

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
	{
		// [LOGGING]
		std::string msg = "Setting socket options" + intToString(sock);
		//perror(msg.c_str());
		exit(EXIT_FAILURE);
	}
	set_connection(connect_to_network(sock, address));
	if (setNonBlocking(sock) == false)
	{
		// [LOGGING]
		//perror("setting non-blocking");
		exit(EXIT_FAILURE);
	}
	test_connection(get_connection());
}

BindingSocket::BindingSocket( BindingSocket & src ): SimpleSocket(src)
{
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BindingSocket::~BindingSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BindingSocket &				BindingSocket::operator=( BindingSocket & rhs )
{
	if ( this != &rhs )
        SimpleSocket::operator=(rhs);
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/


int BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	int	ret = 0;

	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	if (ret < 0)
	{
		// [LOGGING]
		std::string msg = "Binding socket " + intToString(sock);
		perror(msg.c_str());
		close(sock);
	}
	return (ret);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
