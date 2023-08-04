
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "../Settings/Directives/Cgi.hpp"

namespace FT {
	class Cgi_handler {
		public:
			Cgi_handler();
			~Cgi_handler();
			Cgi_handler (Cgi_handler &other);
			Cgi_handler& operator=(const Cgi_handler &other);

            int open_socketpair();
            int open_socketpair(int *fd_pair);
            int cgi_handler(std::string parsed_req);
            void handle_php();
            void handle_python();

        private:
            int socketpair_fd[2];
            FT::Cgi cgi_config;
	};
}

