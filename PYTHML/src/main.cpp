#include "parser.hpp"
#include "file.hpp"
#include "runner.hpp"
#include "format.hpp"

/**
 * @file main.cpp
 * @author Raj Pandya
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */


int main(int argc, char* argv[]) {
    Parser parse;        // parses all HTML code and breaks it down
    File file;           // all file related operations in this class
    Runner runner;       // all code related to python execution is in this class
    Formatter formatter; // all code related to formatting HTML is in this class
    
    std::vector<std::string> lines = file.read_file(argc, argv);   

    parse.valid_python_tag(lines);
    std::vector<std::string> python_code = parse.parse_python_code(lines);
    std::vector<std::string> executed_code = runner.execute_python_code(python_code);
    std::vector<std::string> embedded_code = file.embed_python_code(lines, executed_code);
    const std::vector<std::string> formatted_code = formatter.format_html(embedded_code);
    file.html_to_file(formatted_code, argv[1]+std::string("_formatted.html"));




    // for (const std::string& line : python_code) {
    //     std::cout << "START" << line << "END" <<std::endl;
    // }

    // for (const std::string& line : embedded_code) {
    //     std::cout << line << std::endl;
    // }

    return EXIT_SUCCESS;
}
