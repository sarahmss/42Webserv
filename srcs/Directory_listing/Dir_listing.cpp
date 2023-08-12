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

int FT::Dir_listing::_check_is_dir(std::string full_path) {

    struct stat path_stat;

    stat(full_path.c_str(), &path_stat);
    return (S_ISDIR(path_stat.st_mode));
}

void FT::Dir_listing::_add_style(std::string &buff,
        std::string &font_family,
        std::string &dir_img) {
    buff += "<style>";
    buff += "body { font-family: \'" + font_family + "\';}";
    buff += "ul { list-style-type: none; }";
    buff += ".dir-bullet::before {content: \'\'; display: inline-block; width: 20px; height: 20px;";
    buff += "background-image: url(\'" + dir_img + "\');background-size: cover; margin-right: 0.5em;}";
    buff += ".generic-bullet::before { content: \"\\2022\"; margin-right: 0.5em }\n";
    buff += "</style>";
}

void FT::Dir_listing::_add_h1(std::string &buff, std::string content) {
    buff += "<h1> Listing from: " + content + "</h1>";
}

void FT::Dir_listing::_add_anchor_link(std::string &buff,
        std::string filename,
        std::string &full_path,
        std::string style_class) {
    buff += "<li class=\"" + style_class + "\">"
        + "<a href=\"" + full_path + "/" + filename + "\">" + filename + "</a>"
        + "</li>\n";
}

void FT::Dir_listing::_add_header(std::string &buff,
        std::string page_title,
        std::string font_family,
        std::string dir_img) {
    buff += "<head>";
    buff += "<title>" + page_title + "</title>";
    _add_style(buff, font_family, dir_img);
    buff += "</head>";
}

void FT::Dir_listing::_add_body(std::string &buff,
        std::string &full_path,
        DIR *dir) {

    struct dirent *file = readdir(dir);

    _add_h1(buff, full_path);
    buff += "<hr><ul>";
    while (file) {
        if (file->d_type == DT_DIR)
            _add_anchor_link(buff, file->d_name, full_path, "dir-bullet");
        else
            _add_anchor_link(buff, file->d_name, full_path, "generic-bullet");
        file = readdir(dir);
    }
    buff += "</ul>";
}

std::string FT::Dir_listing::generate_listing_page (std::string root_dir, std::string path = "") {

    std::string full_path = root_dir + "/" + path;
    if (access(full_path.c_str(), F_OK | R_OK | X_OK) == -1)
        throw std::invalid_argument("The file doesn't exist or requires privileges!");
    if (!_check_is_dir(full_path))
        throw std::invalid_argument("The path given it's not a directory!");

    DIR *dir = opendir(full_path.c_str());
    struct dirent *file = readdir(dir);

    std::string page = "<html>";
    _add_header(page,
            "Listing: " + full_path,
            "Arial",
            "https://pluspng.com/img-png/folder-png-folder-icon-1600.png");

    _add_body (page, full_path, dir);
    page += "</html>";
    closedir(dir);
    return page;
}

int main () {
    FT::Dir_listing list_file;
    std::string k = list_file.generate_listing_page("/home/pewpan");
    std::cout << k << std::endl;
    return 0;
}
