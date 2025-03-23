#include "parser.hpp" 

/**
 * @file parser.cpp
 * @author Raj Pandya
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

bool Parser::valid_python_tag(const std::vector<std::string>& lines) {
    bool in_python_block = false;
    int line_number = 0;
    int last_python_line = 0;
    bool valid = true;

    for (const std::string& line : lines) {
        line_number++;
        if (line.find("<python>") != std::string::npos) {
            if (in_python_block) {
                std::cerr << "ERROR: Python tags cannot exist inside other Python tags, close the tag located at line " 
                          << last_python_line << " before using more tags\n";
                valid = false;
            }
            in_python_block = true;
            last_python_line = line_number;
        }

        if (line.find("</python>") != std::string::npos) {
            if (!in_python_block) {
                std::cerr << "ERROR: Closing tag on line " << last_python_line << " does not have an opening tag.\n";
                valid = false;
            }
            in_python_block = false;
            last_python_line = line_number;
        }
    }

    if (in_python_block) {
        std::cerr << "ERROR: Closing tag not found for line " << last_python_line << ".\n";
        valid = false;
    }

    return valid;
}

int Parser::get_min_indentation(const std::vector<std::string>& lines) {
    size_t min_indents = 99999;
    for (const std::string& line : lines) {
        if (!line.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
            continue;
        }
        else {
            size_t leading_spaces = line.find_first_not_of(" \t");
            if (leading_spaces != std::string::npos) {
                min_indents = std::min(min_indents, leading_spaces);
            }
        }
    }
    return min_indents;
}

std::vector<std::string> Parser::remove_white_space(int whitespace, const std::vector<std::string>& lines) {
    std::vector<std::string> python_code;
    python_code.reserve(lines.size());  
    for (const std::string& line : lines) {
        python_code.push_back(line.substr(whitespace));
    }
    return python_code;
}

std::vector<std::string> Parser::parse_python_code(const std::vector<std::string>& lines) {
    std::vector<std::string> python_code;
    int line_number = 0;

    while (line_number < lines.size()) {
        if (lines[line_number].find("<python>") != std::string::npos) {
            line_number++;
            while (line_number < lines.size() && 
            lines[line_number].find("</python>") == std::string::npos) {
                if (lines[line_number].find_first_not_of(" \t\n\r\f\v") != std::string::npos)
                    python_code.push_back(lines[line_number]);
                line_number++;
            }
        }
        line_number++;
    }

    int min_indent = get_min_indentation(python_code);
    python_code = remove_white_space(min_indent, python_code);

    return python_code;
}
