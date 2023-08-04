/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:51 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 21:44:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESERVER_HPP
# define SIMPLESERVER_HPP

# include <iostream>
# include <string>

#include "./Sockets/Sockets.hpp"

namespace FT
{
	class SimpleServer
	{
		public:

			SimpleServer(void);
			virtual ~SimpleServer();

			virtual void		launch(void) = 0;
			ListeningSocket		*get_socket();
			void				init(int domain, int service, int protocol, int port, unsigned long int interface, int bklg);

		private:
			ListeningSocket	*socket;
			virtual void accepter(void) = 0;
			virtual void handler(void) = 0;
			virtual void responder(void) = 0;
	};
}

#endif /* **************************************************** SIMPLESERVER_H */
