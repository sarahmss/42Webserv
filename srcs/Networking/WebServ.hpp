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


# include <string.h>
# include <unistd.h>
# include "./SimpleServer.hpp"
# include "../httpMessages/Request/RequestParser.hpp"
# include "../httpMessages/Request/Request.hpp"
#include "../httpMessages/Response/ResponseBuilder.hpp"

namespace FT
{
		class WebServ: public SimpleServer
	{
		public:

			WebServ(ServerVecType confs);
			~WebServ();

			void launch(void);

		private:
			int				_newSocket;
			ResponseBuilder	resp_build;
			ServerVecType	_serversConfs;
			int				_port;

			void	accepter();
			void	handler();
			void	responder();
	};
}



#endif /* ******************************************************* WebServ_H */
