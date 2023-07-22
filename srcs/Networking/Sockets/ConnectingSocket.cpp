#include "ConnectingSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface):
	SimpleSocket(domain, service, protocol, port, interface)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
}

FT::ConnectingSocket::ConnectingSocket( ConnectingSocket & src ): FT::SimpleSocket(src)
{
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ConnectingSocket::~ConnectingSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ConnectingSocket &				FT::ConnectingSocket::operator=( ConnectingSocket & rhs )
{
	if ( this != &rhs )
        FT::SimpleSocket::operator=(rhs);
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

int FT::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	return (connect(sock, (struct sockaddr *)&address, sizeof(address)));
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
