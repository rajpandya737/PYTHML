#pragma once

/**
 * @file format.hpp
 * @author Raj Pandya
 * @brief This class formats and corrects HTML strings
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <string>
#include <tidy.h>
#include <tidybuffio.h>
#include <vector>
#include <stack>

class Formatter
{
public:
    const std::vector<std::string> format_html(const std::vector<std::string> &input_html);

private:
    const char *flatten_vector_to_string(const std::vector<std::string> &input_html);
};