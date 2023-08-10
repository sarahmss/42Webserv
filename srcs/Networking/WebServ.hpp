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

typedef std::map<int, ConfsVecType>	PortServerType;
typedef std::vector<FT::SimpleServer *>	SimpleServerVecType;

namespace FT
{
		class WebServ
	{
		public:

			WebServ(ConfsVecType confs);
			~WebServ();

			void	launch(void);

		private:
			PollHandler			_epoll;
			SimpleServerVecType	_simpleServers;
			ConfsVecType		_serversConfs;
			PortServerType		_portServer;
			size_t				_backLog;
			ResponseBuilder		resp_build;

			void			_groupServers(void);
			void			_initServers(void);
			void			_addToPoll(SimpleServer *newServer);
			void			_removeFromPoll(int fd);
			void			_coreLoop(void);
			void			_accepter(SimpleServer *server);
			void			_handler(SimpleServer* server);
			void			_responder(SimpleServer* server);
	};
}

#endif /* ******************************************************* WebServ_H */
