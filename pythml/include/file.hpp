#pragma once

/**
 * @file file.hpp
 * @author Raj Pandya
 * @brief This class handles all functionality related to files, primarily reading and writing
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class File
{
public:
    std::vector<std::string> embed_python_code(std::vector<std::string>, const std::vector<std::string> &);
    void html_to_file(const std::vector<std::string> &, const std::string &);
    std::vector<std::string> read_file(int, char *[]);
};