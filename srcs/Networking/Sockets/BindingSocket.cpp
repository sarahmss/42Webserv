/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:44 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindingSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BindingSocket::BindingSocket(int domain, int service, int protocol, int port, unsigned long interface):
	SimpleSocket(domain, service, protocol, port, interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
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
	return (bind(sock, (struct sockaddr *)&address, sizeof(address)));
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
