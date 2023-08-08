

#include "Cgi_handler.hpp"
#include <utility>

FT::Cgi_handler::Cgi_handler () {
    _cgi_program_list.addProgram("php", "/usr/bin/php-cgi");
    _env.insert(std::make_pair("Make something", "Make something"));
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
// fd[0] -> child
// fd[1] -> parent
int FT::Cgi_handler::_open_socketpair() {
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, _socketpair_fd))
        return -1;
    return 0;
}

std::string FT::Cgi_handler::_get_extension(std::string req_path) {
    int index = req_path.find_last_of(".") + 1;
    if (index == -1)
        return "";
    return req_path.substr(index);
}

int FT::Cgi_handler::cgi_handler(
        std::string root_directory,
        std::string req_script,
        std::string body) {

    int status;
    std::string extension = _get_extension(req_script);
    std::string full_path = root_directory + "/" + req_script;

    if (extension == "")
        return (-1);

    this->_open_socketpair();
    int child_pid = fork();
    if (child_pid == -1)
        std::cerr << "Failure at fork()" << std::endl;

    if (child_pid > 0) {
        close(_socketpair_fd[0]);
        waitpid(child_pid, &status, 0);
    }
    else
        _handler(root_directory, req_script, extension, body);

    close(_socketpair_fd[1]);
    return 0;
}

char const **FT::Cgi_handler::_make_env_list(std::vector<const char *> &env_vector) {
    for (env_var_t::iterator iter = _env.begin(); iter != _env.end(); iter++ ) {
        std::string buff = iter->first + "=" + iter->second;
        env_vector.push_back(buff.c_str());
    }
    env_vector.push_back(NULL);
    return env_vector.data();
}

void FT::Cgi_handler::_handler(
        std::string root_directory,
        std::string req_script,
        std::string extension,
        std::string body = "") {

    std::string program = _cgi_program_list.getProgram(extension);
    std::vector<const char *> env_vector;

    char const **envp = _make_env_list(env_vector);

    dup2(STDOUT_FILENO, _socketpair_fd[0]);
    execve(program.c_str(), NULL, const_cast<char **>(envp)); 
    close(_socketpair_fd[0]);
    close(_socketpair_fd[1]);
    exit(-1);
}
