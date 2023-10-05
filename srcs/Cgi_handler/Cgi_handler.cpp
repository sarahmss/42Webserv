
#include "Cgi_handler.hpp"
#include <cstdlib>
#include "../multiplexing/PollHandler.hpp"
#include <ctime>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>


void static _ft_sleep(unsigned int milliseconds) {
    clock_t start = std::clock();
    clock_t delay = milliseconds * CLOCKS_PER_SEC / 1000;

    while (std::clock() - start < delay)
		continue ;
}

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

int FT::Cgi_handler::_check_file(
		std::string filename,
		int flags,
		std::string error_code,
		std::string &responseCode) {

	if (access(filename.c_str(), flags)) {
		responseCode = error_code;
		return 1;
	}
	return 0;
}

std::string FT::Cgi_handler::_parent_side(
		int child_pid,
		std::string &responseCode) {

	char buff[100000];
	pid_t child_wait;
	int status;

	int wait_steps = 0;
	for (; wait_steps < WAIT_MAX; wait_steps++) {

		child_wait = waitpid(child_pid, &status, WNOHANG);

		if (child_wait && (WIFEXITED(status) == 0 || WEXITSTATUS(status))) {
			close(_socketpair_fd[0]);
			responseCode = "500";
			return "";
		}

		if (child_wait && WIFEXITED(status)) {
			ssize_t read_quant_bytes = read(_socketpair_fd[0], buff, 100000);
			if (read_quant_bytes >= 100000) {
				close(_socketpair_fd[0]);
				responseCode = "413";
				return "";
			}
			if (read_quant_bytes < 0) {
				close(_socketpair_fd[0]);
				responseCode = "500";
				return "";
			}
			buff[read_quant_bytes] = 0;
			break ;
		}

		_ft_sleep(WAIT_MS);
	}

	if (wait_steps == WAIT_MAX) {
		kill(child_pid, SIGKILL);
		wait(NULL);
		responseCode = "500";
		return "";
	}

	return std::string(buff);
}


// Return value meaning
// 1 = no extension specified
// 0 = Success
// -1 = Failure at some point
std::string FT::Cgi_handler::cgi_handler(
		std::string &responseCode,
		std::map<std::string,
		std::string> &env) {

	std::string response_body;
		
	if (_check_file(env["SCRIPT_FILENAME"], F_OK, "404", responseCode),
			_check_file(env["SCRIPT_FILENAME"], X_OK | R_OK, "403", responseCode))
		return "";

	if (_open_socketpair())  {
		responseCode = "500";
		return "";
	}

	int child_pid = fork();

	if (child_pid < 0) {
		close(_socketpair_fd[0]);
		close(_socketpair_fd[1]);
		responseCode = "500";
		return "";
	}

	if (child_pid == 0)
		_handler(env);
	else {
		close(_socketpair_fd[1]);
		response_body = _parent_side(child_pid, responseCode);
	}
	close(_socketpair_fd[0]);
	return response_body;
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
		if (buff.size() > 500) // Exit if it's too large
			exit(1);

		std::strcpy(envp_buff[idx], buff.c_str());
		idx += 1;
	}
	envp_buff[env.size()][0] = 0;
}

