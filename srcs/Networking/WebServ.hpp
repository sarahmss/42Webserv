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
# include "./SimpleServer.hpp"

typedef std::vector<SimpleServer *>	SimpleServerVecType;
typedef std::pair<AcceptingSocket *, SimpleServer *> ConnectionType;
typedef std::vector<t_channel *> ChannelsVecType;

class WebServ
{
	public:

		WebServ(ConfsVecType confs);
		~WebServ();
  	std::string	concatenate_string(std::string s1, std::string s2);
		std::string	concatenate_int(std::string s1, int n2);

		void	launch(void);

	private:
		PollHandler			_epoll;
		SimpleServerVecType	_simpleServers;
		ConfsVecType		_serversConfs;
		ChannelsVecType		_serverChannels;
		size_t				_backLog;
		Handler				_handler;
		Responder			_responder;

		void			_initServers(void);

		void	_addServerToPoll(SimpleServer *newServer);
		void	_addConnectionsToPoll(AcceptingSocket *acc, SimpleServer *serv);
		void	_removeConnectionFromPoll(ConnectionType *cnc, t_channel *chnl);
		void	_coreLoop(void);
		void	_launchAccepter(SimpleServer *server);
		void	_launchHandler(SimpleServer *server, AcceptingSocket *accept);
		void	_launchResponder(SimpleServer *server, AcceptingSocket *accept);
};

#endif /* ******************************************************* WebServ_H */
