/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:44 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::WebServ::WebServ(ServerVecType confs)
{
	_serversConfs = confs;
	_backLog = 50;
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::WebServ::~WebServ() {
	for (size_t i = 0; i < _simpleServers.size(); i++)
		if (_simpleServers[i])
			delete _simpleServers[i];
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	FT::WebServ::launch(void)
{
	_groupServers();
	_initServers();
}

/*
	@brief: Group Servers defined in conf file by ports number
*/
void	FT::WebServ::_groupServers(void)
{
	for (size_t i =0; i < _serversConfs.size(); i++)
	{
		int port = _serversConfs[i].getListen().getPort();
		_portServer[port].push_back(_serversConfs[i]);
	}
}

void	FT::WebServ::_initServers(void)
{
	PortServerType::iterator	begin = _portServer.begin();
	PortServerType::iterator	end = _portServer.end();

	for (; begin != end; begin++)
	{
		SimpleServer	*newServer = new SimpleServer(begin->first, _backLog);
		_simpleServers.push_back(newServer);
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
