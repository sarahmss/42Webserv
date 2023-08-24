/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:55:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/23 23:38:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Responder::Responder(void):	_protocolVersion("HTTP/1.1"),
							_sttsCode("200"),
							_reasonPhrase("OK"),
							_body(""),
							_header()
{
	_header["Server"] = "webserv";
	_header["Content-type"] = "text/html";
	_header["Connection"] = "close";
	return ;
}

void	Responder::launch(int clientSocket, std::string serverName, std::string sttsCode, std::string body, strPairType headerField)
{
	_clientSocket = clientSocket;
	_body = body;
	_sttsCode = sttsCode;
	if (headerField.first != "" && headerField.second != "")
		_header[headerField.first] = headerField.second;
	_header["Server"] = serverName;
	// _header["date"] = ; gerenciar data
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

void	Responder::sendResponse(void)
{
	HeadersType::iterator it = _header.begin();
	HeadersType::iterator end = _header.end();

	// [LOGGING]
	std::cout << " ++ Building response" << std::endl;
	_respBuilder.add_protocol_status(_protocolVersion, _sttsCode);
	for (; it != end; ++it)
		_respBuilder.add_value_pair(it->first, it->second);
	_respBuilder.add_body(_respBuilder.build_body(_body));

	// [LOGGING]
	std::cout << " ++ Sending Response" << std::endl;
	if (send(_clientSocket, _respBuilder.get_cresponse(), _respBuilder.get_response_size(), 0) < 0)
		throw std::runtime_error("Error sending response");

	// [LOGGING] DEBUG LEVEL == true
	//std::cout << _respBuilder.get_response() << std::endl;
	_respBuilder.reset();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
