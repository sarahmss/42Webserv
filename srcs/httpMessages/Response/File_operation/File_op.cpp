
#include "File_op.hpp"

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
    return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
  throw std::runtime_error("Error opening file");
}

std::string get_file_contents(std::string filename)
{
    return get_file_contents(filename.c_str());
}
