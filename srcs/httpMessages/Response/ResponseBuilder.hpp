
#include <map>
#include <vector>
#include <string>

// This class will only build the sections for the http response
// No security checks will be done here

#ifndef RESPONSE_BUILDER
#define RESPONSE_BUILDER

	class ResponseBuilder {
		public:
			ResponseBuilder();
			~ResponseBuilder();
			ResponseBuilder( ResponseBuilder & src);
			ResponseBuilder& operator=(const ResponseBuilder& other);

			std::string build_body(std::string body);
			std::string build_body_with_file(std::string path);
			std::string build_content_len(std::string &response);
			std::string build_value_pair(std::string header, std::string value);
			std::string build_protocol_status(std::string protocol_and_version, std::string code);

			void add_body(std::string body);
			void add_body_with_file(std::string path);
			void add_content_len(std::string &response);
			void add_value_pair(std::string header, std::string value);
			void add_protocol_status(std::string protocol_and_version, std::string code);
			std::string get_response();
			const char *get_cresponse();
			size_t get_response_size();
			void reset();

		private:
			std::map<std::string, std::string> _code_description;
			std::string response;
	};
#endif
