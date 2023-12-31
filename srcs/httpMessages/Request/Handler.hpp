/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/10/03 21:34:08 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include <iostream>
#include <netinet/in.h>
# include <string>
# include <sys/socket.h>
# include <queue>
# include "../Utils.hpp"
# include "../../Cgi_handler/Cgi_handler.hpp"
# include "../../Settings/Parser.hpp"
#include "../Response/Responder.hpp"
# include "./RequestParser.hpp"
# include "./../../global.hpp"
# include <dirent.h>

typedef std::priority_queue<Location> LocationQueueType;
class Handler
{
	public:
		Handler(void);
		Handler(int clientSocket, ServerConf conf, struct sockaddr_in &address);
		~Handler();

		void				ParseRequest(void);
		void				launch(void);

		RequestParser		getRequestParser(void);
		
		std::string			response_code;
		vecPairType			headerField;
		strPairType			Response;

	private:
		int					_clientSocket;
		RequestParser		_requestParsed;
		ServerConf			_conf;
		Location			_location;
		bool				_locationSet;
		std::string			_serverName;
		std::string			_uri;
		std::string			_method;
		unsigned int		_client_port;
		char 				_client_ip_address[INET_ADDRSTRLEN];


		void				_checkRequest();
		void				_selectLocation(void);
		void				_loadErrorPage(std::string code, std::string message);

		std::string			_setPrefix(Location location);

		LocationQueueType	_checkLocation(void);
		bool				_checkRedirection(void);
		void				_checkMethod(void);

		void				_setBody(void);
		std::string			_setPath(void);

		void				_launchPost(void);
		void				_launchGet(std::string path);
		void				_launchDelete(std::string path);
		void				_launchCGI(std::string path);

		bool				_checkCgi(std::string path);
		void				_checkPayload(void);
		void				_prepare_env_map(std::map<std::string, std::string> &env_map, std::string path, std::string body);
};

#endif /* *************************************************** Request_H */
