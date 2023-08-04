

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
// Instead of opening two pipes
// Achieve interprocess communication
// Init internal fd using socketpair
int FT::Cgi_handler::open_socketpair() {
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socketpair_fd))
        return -1;
    return 0;
}

// If needed init external fd 
int FT::Cgi_handler::open_socketpair(int *fd_pair) {
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd_pair))
        return  -1;
    return 0;
}

/*
int FT::Cgi_handler::cgi_handler(std::string parsed_req) {

    this->open_socketpair();
    int child_pid = fork();
    if (child_pid == -1)
        std::cerr << "Failure at fork()" << std::endl;
    if (parsed_req == "some extension") {
        find_file;
        if not found return 404
        if found fork process and execute the script
        use socketpair to send and receive data between process
        }
    }
    return (0);
}

void FT::Cgi_handler::handler_php() {
    dup2(STDOUT_FILENO, socketpair_fd[0]);
    execve();
}
void FT::Cgi_handler::handle_python() {
    dup2(STDOUT_FILENO, socketpair_fd[0]);
    execve();
}
*/
