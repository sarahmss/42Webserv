/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:56:24 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Listen.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Listen::Listen(): _host(std::string()), _port(int()) { return ; }

FT::Listen::Listen( const Listen & src ) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Listen::~Listen() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::Listen	&FT::Listen::operator=( FT::Listen const & rhs )
{
	if ( this != &rhs )
	{
		this->_host = rhs.getHost();
		this->_port = rhs.getPort();
	}
	return *this;
}

std::ostream	&FT::operator<<( std::ostream & o, FT::Listen const & i )
{
	o	<< "Host = " << i.getHost() << std::endl
		<< "Port =" << i.getPort() << std::endl;

	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool	FT::Listen::IsSet(void) const
{
	if (_port == int())
		return false;
	return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	FT::Listen::getHost(void) const
{
	return _host;
}

int	FT::Listen::getPort(void) const
{
	return _port;
}

void	FT::Listen::SetHost(std::string host)
{
	_host = host;
}

void	FT::Listen::SetPort(int port)
{
	_port = port;
}
/* ************************************************************************** */
