/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:40 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 21:43:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::SimpleServer::SimpleServer(void)
{ return ; }

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

void	FT::SimpleServer::init(int domain, int service, int protocol, int port, unsigned long int interface, int bklg)
{
	socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

FT::ListeningSocket * FT::SimpleServer::get_socket()
{
	return (socket);
}
/* ************************************************************************** */
