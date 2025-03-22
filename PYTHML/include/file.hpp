#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class File{
public:
    std::vector<std::string> embed_python_code(std::vector<std::string>, const std::vector<std::string>&);
    void html_to_file(const std::vector<std::string>&, const std::string&);
    std::vector<std::string> read_file(int, char*[]);

};