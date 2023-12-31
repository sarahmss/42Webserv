/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:56:24 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/24 16:12:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Listen.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Listen::Listen(): _host(std::string("localhost")), _port(int()) { return ; }

Listen::Listen( const Listen & src ) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Listen::~Listen() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Listen	&Listen::operator=( Listen const & rhs )
{
	if ( this != &rhs )
	{
		this->_host = rhs.getHost();
		this->_port = rhs.getPort();
	}
	return *this;
}

std::ostream	&operator<<( std::ostream & o, Listen const & i )
{
	o	<< "Host = " << i.getHost() << std::endl
		<< "Port =" << i.getPort() << std::endl;

	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool	Listen::IsSet(void) const
{
	if (_port == int())
		return false;
	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	Listen::getHost(void) const
{
	return _host;
}

int	Listen::getPort(void) const
{
	return _port;
}

void	Listen::SetHost(std::string host)
{
	_host = host;
}

void	Listen::SetPort(int port)
{
	_port = port;
}
/* ************************************************************************** */
