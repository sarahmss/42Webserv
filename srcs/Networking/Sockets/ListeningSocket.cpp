#include "ListeningSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ListeningSocket::ListeningSocket(int domain, int service, int protocol,  int port, unsigned long interface, int bklog):
BindingSocket(domain, service, protocol, port, interface)
{
	backlog = bklog;
	start_listening();
	test_connection(listening);

}

FT::ListeningSocket::ListeningSocket( ListeningSocket & src ): FT::BindingSocket(src)
{
	this->listening = src.listening;
	this->backlog = src.backlog;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ListeningSocket::~ListeningSocket()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ListeningSocket &				FT::ListeningSocket::operator=( ListeningSocket  & rhs )
{
	if ( this != &rhs )
	{
        FT::BindingSocket::operator=(rhs);
		this->listening = rhs.get_listening();
		this->backlog = rhs.get_backlog();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void FT::ListeningSocket::start_listening()
{
	listening = listen(get_sock(), backlog);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int FT::ListeningSocket::get_listening()
{
	return (listening);
}

int FT::ListeningSocket::get_backlog()
{
	return (backlog);
}
/* ************************************************************************** */
