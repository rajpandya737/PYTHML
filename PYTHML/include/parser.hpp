#pragma once

#include <vector>
#include <string>
#include <iostream>

class Parser {
public:
    bool valid_python_tag(const std::vector<std::string>& lines);
    int get_min_indentation(const std::vector<std::string>& lines);
    std::vector<std::string> remove_white_space(int whitespace, const std::vector<std::string>& lines);
    std::vector<std::string> parse_python_code(const std::vector<std::string>& lines);
};
