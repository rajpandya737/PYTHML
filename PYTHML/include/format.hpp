#pragma once

#include <string>
#include <tidy.h>
#include <tidybuffio.h>
#include <vector>
#include <stack>

class Formatter{
public:
    const std::vector<std::string> format_html(const std::vector<std::string>& input_html);
private:
    const char* flatten_vector_to_string(const std::vector<std::string>& input_html);
};