#include <fstream>
#include <iostream>
#include <sstream>

std::string rtrvfile(std::string path) {
    std::ostringstream ss;
    std::ifstream file(path);
    if (file.is_open())
        ss << file.rdbuf();

    return ss.str();
}

void savefile(std::string path, std::string content) {
    std::ofstream file(path);
    file << content;
    file.close();
}
