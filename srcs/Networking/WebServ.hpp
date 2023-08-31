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

			void		launch(void);
			std::string	concatenate_string(std::string s1, std::string s2);
			std::string	concatenate_int(std::string s1, int n2);

			private:
			PollHandler			_epoll;
			SimpleServerVecType	_simpleServers;
			ConfsVecType		_serversConfs;
			PortServerType		_portServer;
			size_t				_backLog;
			Handler				_handler;
			Responder			_responder;

			void			_groupServers(void);
			void			_initServers(void);
			void			_addToPoll(SimpleServer *newServer);
			void			_removeFromPoll(int fd);
			void			_coreLoop(void);
			void			_launchAccepter(SimpleServer *server, struct sockaddr_in &client_addr);
			void			_launchHandler(SimpleServer* server,  struct sockaddr_in &client_addr);
			void			_launchResponder(SimpleServer* server);
	};

#endif /* ******************************************************* WebServ_H */
