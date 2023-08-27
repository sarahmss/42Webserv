
#ifndef DIR_LISTING
#define DIR_LISTING

#include <dirent.h>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

namespace FT {
	class Dir_listing {
		public:
			Dir_listing();
			~Dir_listing();
			Dir_listing (Dir_listing &other);
			Dir_listing& operator=(const Dir_listing &other);
            
            std::string generate_listing_page(std::string root_dir, std::string path);

        private:
            int _check_is_dir(std::string full_path);

			void _add_simple_bullet(std::string &buff,
					std::string bullet_name,
					std::string symbol);

			void _add_img_bullet(std::string &buff,
					std::string bullet_name,
					std::string url_path);

            void _add_header(std::string &buff,
                    std::string page_title,
                    std::string font_family,
                    std::string dir_img);

            void _add_body(std::string &buff, std::string &full_path, DIR *dir);

            void _add_anchor_link(std::string &buff,
                    std::string filename,
                    std::string &full_path,
                    std::string style_class);

            void _add_style(std::string &buff, std::string &font_family, std::string &dir_img);
            void _add_h1(std::string &buff, std::string content);

	};
}

#endif
