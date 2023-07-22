/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:38:34 by smodesto          #+#    #+#             */
/*   Updated: 2023/06/26 21:58:44 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIMPLESOCKET_HPP
# define SIMPLESOCKET_HPP

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>

/*
	@Attributtes
		- address:
		- connection:
		- sock:

*/
namespace FT
{
	class SimpleSocket
	{
		public:

			SimpleSocket(int domain, int service, int protocol, int port, unsigned long interface);
			SimpleSocket( SimpleSocket & src );
			~SimpleSocket();

			virtual int			connect_to_network(int sock, struct sockaddr_in address) = 0;
			void				test_connection(int item_to_test);

			struct sockaddr_in	get_address();
			int					get_sock();
			int					get_connection();
			void				set_connection(int con);
			void				set_sock(int sck);
			void				set_address(struct sockaddr_in add);


			FT::SimpleSocket &		operator=( FT::SimpleSocket & rhs );

		private:
			struct sockaddr_in address;
			int connection;
			int sock;

	};
}
#endif /* **************************************************** SIMPLESOCKET_HPP */
