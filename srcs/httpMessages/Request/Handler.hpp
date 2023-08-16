/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:45:06 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include <iostream>
# include <string>
# include <queue>
# include "../../Settings/Parser.hpp"
#include "../Response/Responder.hpp"
# include "./RequestParser.hpp"


typedef std::priority_queue<Location> LocationQueueType;


	class Handler
	{
		public:
			Handler(int clientSocket, ServerConf conf);
			~Handler();

			void				launch(void);
			RequestParser		getRequestParser(void);

			strPairType			codeDescription;
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


			void				_checkRequest(void);
			void				_selectLocation(void);
			LocationQueueType	_checkLocation(void);
			std::string			_setPrefix(Location location);
			bool				_checkRedirection(void);
			void				_checkMethod(void);
			void				_setBody(void);
			std::string			_setPath(void);
			void				_launchPost(void);
			void				_launchGet(std::string path);
			void				_launchDelete(std::string path);
			void				_checkPayload(void);
	};

#endif /* *************************************************** Request_H */
