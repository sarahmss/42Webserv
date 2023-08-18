
#include "Dir_listing.hpp"

int main(void) {
	FT::Dir_listing dir = FT::Dir_listing();

	std::string page = dir.generate_listing_page("/home/pewpan/Prog", "42SP");
	std::cout << page << std::endl;
}
