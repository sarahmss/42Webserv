/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:02:43 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/01 21:20:18 by smodesto         ###   ########.fr       */
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
