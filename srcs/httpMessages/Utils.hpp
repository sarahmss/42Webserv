/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:41:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/02 00:42:00 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
#include <map>

#define CRLF "\r\n"
#define CRLF2X "\r\n\r\n"
#define BUFFSIZE 5

namespace FT
{
	typedef std::map<std::string, std::string>	HeadersType;
	typedef std::pair<std::string, std::string>	RequestPairType;

	bool		MapHasKey(HeadersType map, std::string key);
	std::string	GetMapItem(HeadersType map, std::string key);
	std::string	GetSockStreamLine(int socketFd);
}

#endif // UTILS_HPP
