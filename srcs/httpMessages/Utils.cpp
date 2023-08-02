/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:02:43 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/02 00:40:42 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/*
	@brief Return true if map contains key
*/
bool	FT::MapHasKey(FT::HeadersType map, std::string key)
{
	return (map.find(key) != map.end());
}

std::string	FT::GetMapItem(FT::HeadersType map, std::string key)
{
	if (MapHasKey(map, (key)))
		return (map[(key)]);
	return ("");
}

std::string	FT::GetSockStreamLine(int socketFd)
{
	ssize_t		bytes = 0;
	char		buffer[BUFFSIZE]= {0};
	std::string	Line;

	while (true)
	{
		bytes = recv(socketFd, buffer, 1, 0);
		if (bytes == -1)
			throw(std::runtime_error("Failed reading from socket!"));
		if (bytes == 0)
			break;
		Line.append(buffer, bytes);
		memset(buffer, 0, BUFFSIZE);
		if (Line.rfind(CRLF) != std::string::npos)
			break;
	}
	return (Line);
}
