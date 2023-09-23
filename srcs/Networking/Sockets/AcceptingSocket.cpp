/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AcceptingSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:49:23 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/31 11:22:21 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AcceptingSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

AcceptingSocket::AcceptingSocket(void)
{
	return ;
}

int AcceptingSocket::startAccepting(int socket)
{
	socklen_t		address_len = sizeof(_clientAddress);

	_clientSocket = accept(socket,
						(struct sockaddr *)&_clientAddress,
						(socklen_t *)&address_len);
	// [LOGGING]
	if (_clientSocket == -1)
		perror("Failed setting clientSocket" );
	if (setNonBlocking(_clientSocket) == false)
		perror("Failed setting NonBlocking" );
	return (_clientSocket);
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

AcceptingSocket::~AcceptingSocket()
{
	return ;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

int	AcceptingSocket::disconnect()
{
	// [Logging]
	std::cout << "++ Connection closed in socket:" + intToString(_clientSocket)<< std::endl;
	if (fcntl(_clientSocket, F_GETFD) != -1)
		return (close(_clientSocket));
	return (-1);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
int	AcceptingSocket::getClientSocket(void)
{
	return (_clientSocket);
}

sockaddr_in	AcceptingSocket::getClientAddress(void)
{
	return (_clientAddress);
}
/* ************************************************************************** */
