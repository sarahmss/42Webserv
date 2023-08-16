/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:49:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ListeningSocket::ListeningSocket(int domain, int service, int protocol,  int port, unsigned long interface, int bklog):
BindingSocket(domain, service, protocol, port, interface)
{
	backlog = bklog;
	startListening();
	test_connection(listening);

}

ListeningSocket::ListeningSocket( ListeningSocket & src ): BindingSocket(src)
{
	this->listening = src.listening;
	this->backlog = src.backlog;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ListeningSocket::~ListeningSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ListeningSocket &				ListeningSocket::operator=( ListeningSocket  & rhs )
{
	if ( this != &rhs )
	{
        BindingSocket::operator=(rhs);
		this->listening = rhs.getListening();
		this->backlog = rhs.getBacklog();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void ListeningSocket::startListening()
{
	listening = listen(get_sock(), backlog);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int ListeningSocket::getListening()
{
	return (listening);
}

int ListeningSocket::getBacklog()
{
	return (backlog);
}
/* ************************************************************************** */
