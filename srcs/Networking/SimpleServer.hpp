/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:51 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 17:20:18 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESERVER_HPP
# define SIMPLESERVER_HPP

# include <iostream>
# include <string>
# include <string.h>
# include <unistd.h>
#include "./Sockets/Sockets.hpp"
# include "../httpMessages/Request/RequestParser.hpp"
# include "../httpMessages/Request/Request.hpp"
#include "../httpMessages/Response/ResponseBuilder.hpp"

namespace FT
{
	class SimpleServer
	{
		public:
			SimpleServer(const int port, int backlog);
			~SimpleServer();

			void			init(void);

			ListeningSocket	*getListeningSocket(void);
			int				getSocket(void);
			int				getClientSocket(void);
			void			setClientSocket(int clientSocket);
			int				getPort(void);
			int				getBacklog(void);

		private:
			ListeningSocket	*socket;
			int				_clientSocket;
			int				_port;
			int				_backlog;
	};
}

#endif /* **************************************************** SIMPLESERVER_H */
