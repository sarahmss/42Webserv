/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:55:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/15 20:30:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Responder::Responder(void) {return ;}

Responder::Responder(int clientSocket, std::string serverName, std::string sttsCode, std::string body, strPairType headerField)
{
	_clientSocket = clientSocket;
	_body = body;
	_sttsCode = sttsCode;
	if (headerField.first != "" && headerField.second != "")
		_header[headerField.first] = headerField.second;
	_header["Server"] = serverName;
	_header["Content-type"] = "text/html";	// quando alterar?
	// _header["date"] = ; gerenciar data
	//_header["Connection"] = "close";
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Responder::~Responder()
{
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Responder::launch (void)
{
	HeadersType::iterator it = _header.begin();
	HeadersType::iterator end = _header.end();

	_respBuilder.add_protocol_status("HTTP/1.1", _sttsCode);
	for (; it != end; ++it)
		_respBuilder.add_value_pair(it->first, it->second);
	_respBuilder.add_body(_respBuilder.build_body(_body));
	if (send(_clientSocket, _respBuilder.get_cresponse(), _respBuilder.get_response_size(), 0) < 0)
		throw std::runtime_error("Error sending response");
	std::cout << _respBuilder.get_response() << std::endl;
	_respBuilder.reset();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
