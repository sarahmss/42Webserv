/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:49:19 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/09 12:20:22 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOCKET_HPP
# define BINDINGSOCKET_HPP

# include <iostream>
# include <string>
# include "SimpleSocket.hpp"
# include "./../../global.hpp"
/*
	This class implements a call to the bind() function of sockets as a deefinition of
	connect_to_network virtual function from SimpleSocket
*/

	class BindingSocket: public SimpleSocket
	{
		public:

			BindingSocket(int domain, int service, int protocol, int port, unsigned long interface);
			BindingSocket( BindingSocket & src );
			~BindingSocket();

			int			connect_to_network(int sock, struct sockaddr_in address);

			BindingSocket &		operator=( BindingSocket & rhs );
	};
#endif /* *************************************************** BINDINGSOCKET_H */
