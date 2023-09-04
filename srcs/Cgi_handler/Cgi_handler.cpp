
#include "Cgi_handler.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>

// php program handler
// python program handler
FT::Cgi_handler::Cgi_handler () {
}

FT::Cgi_handler::~Cgi_handler () {
}

FT::Cgi_handler::Cgi_handler ( Cgi_handler &other ) {
	(void) other;
	return;
}

FT::Cgi_handler& FT::Cgi_handler::operator= ( const Cgi_handler & other ) {
	(void) other;
	return *this;
}

// Using socketpair allow us to have a two way communication
// Instead of opening two pipes Achieve interprocess communication
// Init internal fd using socketpair
// fd[0] -> child
// fd[1] -> parent
int FT::Cgi_handler::_open_socketpair() {
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, _socketpair_fd))
		return -1;
	return 0;
}

// Return value meaning
// 1 = no extension specified
// 0 = Success
// -1 = Failure at some point
std::string FT::Cgi_handler::cgi_handler(
		std::string &responseCode,
		std::map<std::string, std::string> &env,
		std::string body="") {

	char buff[100000];

	if (access(env["SCRIPT_FILENAME"].c_str(), F_OK)) {
		responseCode = "404";
		throw std::runtime_error("File not found");
	}

	if (access(env["SCRIPT_FILENAME"].c_str(), X_OK | R_OK)) {
		responseCode = "403";
		throw std::runtime_error("Not enough privileges");
	}

	if (_open_socketpair())
		throw std::runtime_error("Failure at opening socketPair()");

	int child_pid = fork();

	if (child_pid < 0) {
		close(_socketpair_fd[0]);
		close(_socketpair_fd[1]);
		throw std::runtime_error("Failure at fork()");
	}

	if (child_pid == 0) {
		_handler(env);
	}
	else {
		int status;
		close(_socketpair_fd[1]);

		write(_socketpair_fd[0], body.c_str(), body.size() + 1);
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status) == 0) {
			close(_socketpair_fd[0]);
			responseCode = "500";
			throw std::runtime_error("CGI: Error in the child process");
		}

		ssize_t read_quant_bytes = read(_socketpair_fd[0], buff, 100000);

		if (read_quant_bytes >= 100000) {
			close(_socketpair_fd[0]);
			responseCode = "413";
			throw std::runtime_error("CGI: Response too large");
		}
		buff[read_quant_bytes] = 0;
	}

	close(_socketpair_fd[0]);
	return std::string(buff);
}

// Const cast pode ser usado porque o execve so vai lar
// os arrays de ponteiros char(string)
void FT::Cgi_handler::_handler(std::map<std::string, std::string> &env) {

	std::vector<std::string> env_vector;

	char buff[env.size() + 1][501];
	char *envp[env.size() + 1];
	try {
		_make_list(env, buff);
	} catch (std::exception &e){
		exit(1);
	}

	for (int i = 0; buff[i][0]; i++)
		envp[i] = buff[i];
	envp[env.size()] = 0;

	const char *arg[2];
	arg[0] = env["SCRIPT_NAME"].c_str();
	arg[1] = 0;

	close(_socketpair_fd[0]);

	if (dup2(_socketpair_fd[1], STDIN_FILENO) == -1) {
		close(_socketpair_fd[1]);
		throw std::runtime_error("Unable to dup2 to stdin");
	}

	if (dup2(_socketpair_fd[1], STDOUT_FILENO) == -1) {
		close(_socketpair_fd[1]);
		throw std::runtime_error("Unable to dup2 to stdout");
	}

	execve(env["SCRIPT_FILENAME"].c_str(),
			const_cast<char **>(arg),
			envp); 

	close(_socketpair_fd[1]);
	exit(1);
}

void FT::Cgi_handler::_make_list(
		std::map<std::string, std::string> &env,
		char envp_buff[][501]) {

	std::string buff;
	int idx = 0;
	for (std::map<std::string, std::string>::iterator iter = env.begin();
			iter != env.end(); ++iter) {

		buff = iter->first + "=" + iter->second;
		if (buff.size() > 500)
			throw std::runtime_error("env var too big");

		std::strcpy(envp_buff[idx], buff.c_str());
		idx += 1;
	}
	envp_buff[env.size()][0] = 0;
}
