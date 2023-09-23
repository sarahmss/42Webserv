

#ifndef CGI_HANDLER
#define CGI_HANDLER

# include <sys/socket.h>
# include <sys/wait.h>
# include <unistd.h>

# include <cstring>
# include <map>
# include <cstdlib>
# include <vector>
# include <cstdlib>
#include <stdexcept>
# include <string>

typedef std::map<std::string, std::string> env_var_t;

namespace FT {
	class Cgi_handler {
		public:
			Cgi_handler();
			~Cgi_handler();
			Cgi_handler (Cgi_handler &other);
			Cgi_handler& operator=(const Cgi_handler &other);

		std::string cgi_handler(
				std::string &responseCode,
				std::map<std::string, std::string> &env);

        private:
            void    _not_found();
            void    _error();

			void _handler(std::map<std::string, std::string> &env);

            int         _open_socketpair();

			void _make_list(
					std::map<std::string, std::string> &env,
					char envp[][501]);

            int         _socketpair_fd[2];
            std::string _response;
            env_var_t   _env;
	};
}

#endif

