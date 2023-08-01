/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:41:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 23:10:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "string"
#include "map"
#define CRLF "\r\n"

namespace FT
{
	typedef std::map<std::string, std::string>	HeadersType;
	typedef std::pair<std::string, std::string>	RequestPairType;

	bool		MapHasKey(HeadersType map, std::string key);
	std::string	GetMapItem(HeadersType map, std::string key);

}

#endif // UTILS_HPP
