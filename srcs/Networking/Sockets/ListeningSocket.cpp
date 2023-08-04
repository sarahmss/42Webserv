/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:49:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 16:18:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ListeningSocket::ListeningSocket(int domain, int service, int protocol,  int port, unsigned long interface, int bklog):
BindingSocket(domain, service, protocol, port, interface)
{
	backlog = bklog;
	startListening();
	test_connection(listening);

}

FT::ListeningSocket::ListeningSocket( ListeningSocket & src ): FT::BindingSocket(src)
{
	this->listening = src.listening;
	this->backlog = src.backlog;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ListeningSocket::~ListeningSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ListeningSocket &				FT::ListeningSocket::operator=( ListeningSocket  & rhs )
{
	if ( this != &rhs )
	{
        FT::BindingSocket::operator=(rhs);
		this->listening = rhs.getListening();
		this->backlog = rhs.getBacklog();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void FT::ListeningSocket::startListening()
{
	listening = listen(get_sock(), backlog);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int FT::ListeningSocket::getListening()
{
	return (listening);
}

int FT::ListeningSocket::getBacklog()
{
	return (backlog);
}
/* ************************************************************************** */
