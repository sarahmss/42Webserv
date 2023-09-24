/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:55:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/24 00:14:42 by smodesto         ###   ########.fr       */
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
	_header["AcceptingSocket"] = "close";
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

	sendMessageToLogFile("++Building response", true, 0);
	_respBuilder.add_protocol_status(_protocolVersion, _sttsCode);
	for (; it != end; ++it)
		_respBuilder.add_value_pair(it->first, it->second);
	_respBuilder.add_body(_respBuilder.build_body(_body));

	sendMessageToLogFile("++Sending Response", true, 0);
	logFile << "+++++++++++++++++++++++++++++\n" << _respBuilder.get_response();

	if (send(_clientSocket, _respBuilder.get_cresponse(), _respBuilder.get_response_size(), 0) < 0)
		throw std::runtime_error("Error sending response");
	if (_sttsCode == "413") // Payload too large
		sleep(1);
	_respBuilder.reset();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
