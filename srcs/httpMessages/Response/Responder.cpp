/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:55:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/24 18:05:40 by smodesto         ###   ########.fr       */
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
	_header["AcceptingSocket"] = "close";
	return ;
}

void Responder::_setBodyType(std::string path)
{
	MimeType mimeType = setContentType(path);

	switch (mimeType)
	{
		case JPEG:
			_header["Content-Type"] = "image/jpg";
			break;
		case PNG:
			_header["Content-Type"] = "image/png";
			break;
		case GIF:
			_header["Content-Type"] = "image/gif";
			break;
		case TXT:
			_header["Content-Type"] = "text/plain";
			break;
		case CSS:
			_header["Content-Type"] = "text/css";
			break;
		default:
			_header["Content-Type"] = "text/html";
			break;
	}
}

void Responder::_setLastModified(std::string path)
{
	char		timeBuffer[100];
	std::time_t	time;
	struct stat s;


	if (!isFile(path) || stat(path.c_str(), &s) != 0)
		return;
	memset(timeBuffer, 0, 100);
	time = s.st_mtim.tv_sec;
	std::strftime(timeBuffer, sizeof(timeBuffer),"%a, %d %b %Y %T GMT", std::gmtime(&time));
	_header["Last-Modified"] = timeBuffer;
}

void	Responder::launch(int clientSocket, std::string serverName, std::string sttsCode, strPairType Response, strPairType headerField)
{
	_clientSocket = clientSocket;
	_body = Response.first;
	_sttsCode = sttsCode;
	_setBodyType(Response.second);
	_setLastModified(Response.second);
	if (headerField.first != "" && headerField.second != "")
		_header[headerField.first] = headerField.second;
	_header["Server"] = serverName;
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
