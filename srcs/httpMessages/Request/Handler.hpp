/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 21:58:48 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include <iostream>
# include <string>
# include <queue>
# include "../../Cgi_handler/Cgi_handler.hpp"
# include "../../Settings/Parser.hpp"
#include "../Response/Responder.hpp"
# include "./RequestParser.hpp"


typedef std::priority_queue<Location> LocationQueueType;


	class Handler
	{
		public:
			Handler(void);
			Handler(int clientSocket, ServerConf conf);
			~Handler();

			void				launch(void);
			RequestParser		getRequestParser(void);

			std::string			response_code;
			strPairType			headerField;
			strPairType			getResponsePath;

		private:
			int					_clientSocket;
			RequestParser		_requestParsed;
			ServerConf			_conf;
			Location			_location;
			std::string			_serverName;
			std::string			_uri;
			std::string			_method;


			void				_checkRequest();
			void				_checkCGI(void);

			void				_selectLocation(void);

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

			void				_checkPayload(void);

			std::string			_get_extension(std::string req_path);
	};

#endif /* *************************************************** Request_H */
