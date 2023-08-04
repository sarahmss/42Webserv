/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:51 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:41:26 by smodesto         ###   ########.fr       */
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

			void	launch(void);
			void	init(void);
			ListeningSocket	*get_socket();

		private:
			ListeningSocket	*socket;
			int				_port;
			int				_newSocket;
			int				_backlog;
			ResponseBuilder	resp_build;

			void	accepter();
			void	handler();
			void	responder();
	};
}

#endif /* **************************************************** SIMPLESERVER_H */
