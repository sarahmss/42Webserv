
#include "Cgi_handler.hpp"

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

		if (WIFEXITED(status)) {
			responseCode = "500";
			throw std::runtime_error("CGI: Error in the child process");
		}
		read(_socketpair_fd[0], buff, 100000);
	}

	close(_socketpair_fd[0]);
	return std::string(buff);
}

// Const cast pode ser usado porque o execve so vai lar
// os arrays de ponteiros char(string)
void FT::Cgi_handler::_handler(std::map<std::string, std::string> &env) {

	std::vector<const char *> env_vector;

	char const **envp = _make_list(env, env_vector);

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
			const_cast<char **>(envp)); 

	close(_socketpair_fd[1]);
	exit(1);
}

char const **FT::Cgi_handler::_make_list(
		std::map<std::string, std::string> &env,
		std::vector<const char *> &env_vector) {

	for (env_var_t::iterator iter = env.begin(); iter != env.end(); iter++ ) {
		std::string buff = iter->first + "=" + iter->second;
		env_vector.push_back(buff.c_str());
	}

	env_vector.push_back(NULL);
	return env_vector.data();
}
