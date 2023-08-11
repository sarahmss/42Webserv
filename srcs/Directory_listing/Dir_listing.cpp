
#include "Dir_listing.hpp"

FT::Dir_listing::Dir_listing () {
}

FT::Dir_listing::~Dir_listing () {
}

FT::Dir_listing::Dir_listing ( Dir_listing &other) {
	(void) other;
	return;
}

FT::Dir_listing& FT::Dir_listing::operator= (const Dir_listing & other) {
	(void) other;
	return *this;
}

std::string FT::Dir_listing::generate_listing_page (std::string root_dir, std::string path) {
    std::string full_path = root_dir + "/" + path;
    DIR *dir = opendir(full_path.c_str());

    return "";
}
