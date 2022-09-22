#include <fstream>
#include <iostream>
#include <sstream>

std::string rtrvfile(std::string path) {
    if (path.empty() or path == "/")
        path = "./index.html";

    if (path[0] == '/')
        path = path.insert(0, ".");

    std::ostringstream ss;
    std::ifstream file(path);
    if (file.is_open())
        ss << file.rdbuf();

    return ss.str();
}