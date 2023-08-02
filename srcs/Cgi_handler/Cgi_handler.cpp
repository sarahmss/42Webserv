

#include "Cgi_handler.hpp"
#include <sys/socket.h>

FT::Cgi_handler::Cgi_handler () {
}

FT::Cgi_handler::~Cgi_handler () {
}

FT::Cgi_handler::Cgi_handler ( Cgi_handler &other) {
	(void) other;
	return;
}

FT::Cgi_handler& FT::Cgi_handler::operator= (const Cgi_handler & other) {
	(void) other;
	return *this;
}

// Using socketpair allow us to have a two way communication
int FT::Cgi_handler::open_socketpair() {
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socketpair_fd))
        return -1;
    return 0;
}

int FT::Cgi_handler::open_socketpair(int *fd_pair) {
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd_pair))
        return  -1;
    return 0;
}

/*
int cgi_handler(std::string parsed_req) {
    if (parsed_req == "php") {
        find_file;
        if not found return 404
        if found fork process and execute the script
        use socketpair to send and receive data between process
        }
    }
    return (0);
}

void FT::Cgi_handler::handler_php() {
    return ;
}
void FT::Cgi_handler::handle_python() {
    return ;
}
*/
