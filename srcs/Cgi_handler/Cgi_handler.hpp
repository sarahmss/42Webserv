
# include <sys/socket.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string>
# include "../Settings/Directives/Cgi.hpp"

namespace FT {
	class Cgi_handler {
		public:
			Cgi_handler();
			~Cgi_handler();
			Cgi_handler (Cgi_handler &other);
			Cgi_handler& operator=(const Cgi_handler &other);

            int open_socketpair();
            int cgi_handler(std::string root_directory, std::string parsed_req, std::string body);

        private:
            void handler(std::string root_directory,
                    std::string req_script,
                    std::string extension,
                    std::string body = "");

            std::string get_extension(std::string req_path);

            int _socketpair_fd[2];
            FT::Cgi _cgi_program_list;
            std::string _response;
	};
}

