#ifndef BINDINGSOCKET_HPP
# define BINDINGSOCKET_HPP

# include <iostream>
# include <string>
# include "SimpleSocket.hpp"

/*
	This class implements a call to the bind() function of sockets as a deefinition of
	connect_to_network virtual function from SimpleSocket
*/
namespace FT
{
	class BindingSocket: public SimpleSocket
	{
		public:

			BindingSocket(int domain, int service, int protocol, int port, unsigned long interface);
			BindingSocket( BindingSocket & src );
			~BindingSocket();

			int			connect_to_network(int sock, struct sockaddr_in address);

			BindingSocket &		operator=( BindingSocket & rhs );
	};
}
#endif /* *************************************************** BINDINGSOCKET_H */
