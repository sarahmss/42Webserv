#ifndef CONNECTINGSOCKET_HPP
# define CONNECTINGSOCKET_HPP

# include <iostream>
# include <string>

#include "SimpleSocket.hpp"

/*
	This class implements a call to the connect() function of sockets
	as a definition to the connect_to_network() virtual function from SimpleSocket.
*/

namespace FT
{
	class ConnectingSocket: public SimpleSocket
	{
		public:

			ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface);
			ConnectingSocket( ConnectingSocket & src );
			~ConnectingSocket();

			int connect_to_network(int sock, struct sockaddr_in address);

			ConnectingSocket &		operator=( ConnectingSocket & rhs );
	};
}

#endif /* ************************************************ CONNECTINGSOCKET_H */
