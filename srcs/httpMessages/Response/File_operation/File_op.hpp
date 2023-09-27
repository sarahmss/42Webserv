
#ifndef FILE_OP
#define FILE_OP

#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

std::string get_file_contents(const char *filename);
std::string get_file_contents(std::string filename);

#endif
