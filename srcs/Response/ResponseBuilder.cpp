
#include "../File_operation/File_op.hpp"
#include "ResponseBuilder.hpp"

#include <fstream>
#include <string>

static std::string cast_to_string(int num) {
    std::ostringstream out_stream;
    out_stream << num;
    return (out_stream.str());
}

FT::ResponseBuilder::ResponseBuilder() {
    response = "";
    _code_description.insert(std::make_pair("200", "OK"));
    _code_description.insert(std::make_pair("201", "Created"));
    _code_description.insert(std::make_pair("204", "Not created"));

    _code_description.insert(std::make_pair("302", "Found"));

    _code_description.insert(std::make_pair("400", "Bad Request"));
    _code_description.insert(std::make_pair("401", "Unauthorized"));
    _code_description.insert(std::make_pair("403", "Forbidden"));
    _code_description.insert(std::make_pair("404", "Not found"));

    _code_description.insert(std::make_pair("500", "Internal Error"));
    _code_description.insert(std::make_pair("503", "Service Unavalaible"));
}

FT::ResponseBuilder::~ResponseBuilder() { return ; }

FT::ResponseBuilder::ResponseBuilder( ResponseBuilder & src) {
    (void) src;
    return ;
}

FT::ResponseBuilder& FT::ResponseBuilder::operator=(const ResponseBuilder & other) {
    (void) other;
    return *this;
}

// We must check if the file exist before using this method
std::string FT::ResponseBuilder::build_body_with_file(std::string path) {
    std::string body_section = build_body(get_file_contents(path));
    return body_section;
}

std::string FT::ResponseBuilder::build_content_len(std::string &body) {
    std::string len_section = "Content-Length: ";
    return len_section + cast_to_string(body.size()) + "\n";
}

std::string FT::ResponseBuilder::build_body(std::string body) {
    std::string content_body_section = build_content_len(body);
    content_body_section = "\n" + body;
    return (content_body_section);
}

std::string FT::ResponseBuilder::build_value_pair(std::string header, std::string value) {
    std::string value_pair = header + ": " + value + "\n";
    return value_pair;
}

std::string FT::ResponseBuilder::build_protocol_status(std::string protocol_and_version, std::string code) {
    std::string header_section = protocol_and_version +
        " " + code + " " +
        _code_description[code] + "\n";

    return header_section;
}

void FT::ResponseBuilder::add_body_with_file(std::string path) {
    add_body(get_file_contents(path));
}

void FT::ResponseBuilder::add_content_len(std::string &body) {
    response += "Content-Length: " + cast_to_string(body.size()) + "\n";
}

void FT::ResponseBuilder::add_body(std::string body) {
    add_content_len(body);
    response += "\n" + body;
}

void FT::ResponseBuilder::add_value_pair(std::string header, std::string value) {
    response += header + ": " + value + "\n";
}

void FT::ResponseBuilder::add_protocol_status(std::string protocol_and_version, std::string code) {
    response += protocol_and_version +
        " " + code + " " +
        _code_description[code] + "\n";
}

void FT::ResponseBuilder::reset() {
    response.clear();
}

std::string FT::ResponseBuilder::get_response() {
    return (response);
}

const char *FT::ResponseBuilder::get_cresponse() {
    return (response.c_str());
}

size_t FT::ResponseBuilder::get_response_size() {
    return (response.size());
}
