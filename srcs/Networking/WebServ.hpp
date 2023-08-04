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

# include "./SimpleServer.hpp"

typedef std::map<int, ServerVecType>	PortServerType;
typedef std::vector<FT::SimpleServer *>	SimpleServerVecType;

namespace FT
{
		class WebServ
	{
		public:

			WebServ(ServerVecType confs);
			~WebServ();

			void	launch(void);

		private:
			SimpleServerVecType	_simpleServers;
			ServerVecType		_serversConfs;
			PortServerType		_portServer;
			size_t				_backLog;

			void			_groupServers();
			void			_initServers();

	};
}



#endif /* ******************************************************* WebServ_H */
