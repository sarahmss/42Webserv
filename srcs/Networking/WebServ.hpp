/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:34:08 by smodesto          #+#    #+#             */
/*   Updated: 2023/06/25 19:01:04 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEB_SERV_HPP
#define WEB_SERV_HPP

# include "../multiplexing/PollHandler.hpp"
# include "../httpMessages/Response/Responder.hpp"

typedef std::map<int, ConfsVecType>	PortServerType;
typedef std::vector<SimpleServer *>	SimpleServerVecType;

	class WebServ
	{
		public:

			WebServ(ConfsVecType confs);
			~WebServ();

			void	launch(void);
			void	start_logging_webserv( void );
			void	sendALog_webserv( std::string throw_message);
			void	closeALog_webserv( void );


		private:
			time_t now;
			char *dt;
			PollHandler			_epoll;
			SimpleServerVecType	_simpleServers;
			ConfsVecType		_serversConfs;
			PortServerType		_portServer;
			size_t				_backLog;
			Handler				_handler;
			Responder			_responder;
			std::ofstream		_logFile_webserv;

			void			_groupServers(void);
			void			_initServers(void);
			void			_addToPoll(SimpleServer *newServer);
			void			_removeFromPoll(int fd);
			void			_coreLoop(void);
			void			_launchAccepter(SimpleServer *server);
			void			_launchHandler(SimpleServer* server);
			void			_launchResponder(SimpleServer* server);
	};

#endif /* ******************************************************* WebServ_H */
