
#include "./File_operation/File_op.hpp"
#include "ResponseBuilder.hpp"

#include <fstream>
#include <string>

static std::string cast_to_string(int num) {
    std::ostringstream out_stream;
    out_stream << num;
    return (out_stream.str());
}

ResponseBuilder::ResponseBuilder() {
	response = "";
	_code_description.insert(std::make_pair("200", "OK"));
	_code_description.insert(std::make_pair("201", "Created"));
	_code_description.insert(std::make_pair("204", "Not created"));

	_code_description.insert(std::make_pair("301", "Moved Permanently"));
	_code_description.insert(std::make_pair("302", "Found"));

	_code_description.insert(std::make_pair("400", "Bad Request"));
	_code_description.insert(std::make_pair("401", "Unauthorized"));
	_code_description.insert(std::make_pair("403", "Forbidden"));
	_code_description.insert(std::make_pair("404", "Not found"));
	_code_description.insert(std::make_pair("405", "Method not allowed"));
	_code_description.insert(std::make_pair("413", "Payload too large"));

	_code_description.insert(std::make_pair("500", "Internal Error"));
	_code_description.insert(std::make_pair("501", "Not Implemented"));
	_code_description.insert(std::make_pair("503", "Service Unavalaible"));
	}

ResponseBuilder::~ResponseBuilder() { return ; }

ResponseBuilder::ResponseBuilder( ResponseBuilder & src) {
    (void) src;
    return ;
}

ResponseBuilder& ResponseBuilder::operator=(const ResponseBuilder & other) {
    (void) other;
    return *this;
}

// We must check if the file exist before using this method
std::string ResponseBuilder::build_body_with_file(std::string path) {
    std::string body_section = build_body(get_file_contents(path));
    return body_section;
}

std::string ResponseBuilder::build_content_len(std::string &body) {
    std::string len_section = "Content-Length: ";
    return len_section + cast_to_string(body.size()) + CRLF;
}

std::string ResponseBuilder::build_body(std::string body) {
    std::string content_body_section = build_content_len(body);
    content_body_section = CRLF + body;
    return (content_body_section);
}

std::string ResponseBuilder::build_value_pair(std::string header, std::string value) {
    std::string value_pair = header + ": " + value + CRLF;
    return value_pair;
}

std::string ResponseBuilder::build_protocol_status(std::string protocol_and_version, std::string code) {
    std::string header_section = protocol_and_version +
        " " + code + " " +
        _code_description[code] + CRLF;

    return header_section;
}

void ResponseBuilder::add_body_with_file(std::string path) {
    add_body(get_file_contents(path));
}

void ResponseBuilder::add_content_len(std::string &body) {
    response += "Content-Length: " + cast_to_string(body.size()) + CRLF;
}

void ResponseBuilder::add_body(std::string body) {
    add_content_len(body);
    response += CRLF + body;
}

void ResponseBuilder::add_value_pair(std::string header, std::string value) {
    response += header + ": " + value + CRLF;
}

void ResponseBuilder::add_protocol_status(std::string protocol_and_version, std::string code) {
    response += protocol_and_version +
        " " + code + " " +
        _code_description[code] + CRLF;
}

void ResponseBuilder::reset() {
    response.clear();
}

std::string ResponseBuilder::get_response() {
    return (response);
}

const char *ResponseBuilder::get_cresponse() {
    return (response.c_str());
}

size_t ResponseBuilder::get_response_size() {
    return (response.size());
}
