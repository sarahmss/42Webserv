
#ifndef DIR_LISTING
#define DIR_LISTING

#include <string>
#include <dirent.h>

namespace FT {
	class Dir_listing {
		public:
			Dir_listing();
			~Dir_listing();
			Dir_listing (Dir_listing &other);
			Dir_listing& operator=(const Dir_listing &other);
            
            std::string generate_listing_page(std::string root_dir, std::string path);
	};
}

#endif
