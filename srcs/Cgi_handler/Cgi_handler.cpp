

#include "Cgi_handler.hpp"

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
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, _socketpair_fd))
        return -1;
    return 0;
}

std::string FT::Cgi_handler::get_extension(std::string req_path) {
    int index = req_path.find_last_of(".") + 1;
    if (index == -1)
        return "";
    return req_path.substr(index);
}

int FT::Cgi_handler::cgi_handler(std::string root_directory, std::string req_script, std::string body) {

    int status;
    std::string extension = get_extension(req_script);

    if (extension == "")
        return (-1);

    this->open_socketpair();
    int child_pid = fork();
    if (child_pid == -1)
        std::cerr << "Failure at fork()" << std::endl;

    if (child_pid > 0)
        waitpid(child_pid, &status, 0);
    else
        handler(root_directory, req_script, extension, body);
    return 0;
}

void FT::Cgi_handler::handler(std::string root_directory, std::string req_script, std::string extension, std::string body = "") {
    dup2(STDOUT_FILENO, _socketpair_fd[0]);
    std::string program = _cgi_program_list.getProgram(extension);
    execve(program, NULL, NULL);
    exit(-1);
}

}
