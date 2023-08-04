/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:49:44 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 16:18:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENINGSOCKET_HPP
# define LISTENINGSOCKET_HPP

# include <iostream>
# include <stdio.h>
#include "BindingSocket.hpp"

namespace FT
{
	class ListeningSocket: public BindingSocket
	{

		public:

			ListeningSocket(int domain, int service, int protocol, int port, unsigned long interface, int bklog);
			ListeningSocket( ListeningSocket & src );
			virtual ~ListeningSocket();

			void	startListening();
			int		getListening();
			int		getBacklog();

			ListeningSocket &		operator=( ListeningSocket  & rhs );

		private:
			int backlog;
			int listening;
	};
}

#endif /* ************************************************* LISTENINGSOCKET_H */
