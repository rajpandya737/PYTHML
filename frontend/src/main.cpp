#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <Python.h>
#include <cctype>
#include "lexer.h"


bool valid_python_tag(const std::deque<std::string>& lines) {
    // checks to make sure that there are valid python tags in the HTML file
    // Uses a stack and scans through the HTML file to make sure that the tags are valid
    // Rules for python tags, you cannot have python tags inside of each other
    // One must end before another is open
    // Every open tag must have a closing tag
    // If these rules are not followed, the function will return false
    bool in_python_block = false;
    int line_number = 0;
    int last_python_line = 0;
    bool valid = true;
    for (const std::string& line : lines) {
        line_number++;
        if (line.find("<python>") != std::string::npos) {
            if (in_python_block) {
                std::cerr << "ERROR: Python tags cannot exist inside other Python tags, close the tag located at line " << last_python_line << " Before using more tags\n";
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

std::vector<std::vector<std::string>> parse_python_code(const std::deque<std::string>& lines) {
    // This function will read Python code inside of Python tags
    std::vector<std::vector<std::string>> python_code;
    int line_number = 0;
    while (line_number < lines.size()) {
        if (lines[line_number].find("<python>") != std::string::npos) {
            line_number++;
            std::vector<std::string> code;
            while (lines[line_number].find("</python>") == std::string::npos) {
                code.push_back(lines[line_number]);
                line_number++;
            }
            python_code.push_back(code);
        }
        line_number++;
    }
    return python_code;
}


std::vector<std::vector<std::string>> execute_python_code(const std::vector<std::vector<std::string>>& python_code) {
    std::vector<std::vector<std::string>> executed_code;

    Py_Initialize();

    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* io = PyImport_ImportModule("io");

    for (const std::vector<std::string>& code : python_code) {
        std::string full_code;
        std::vector<std::string> code_output;

        for (const std::string& line : code) {
            full_code += line + "\n";  
        }

        PyObject* new_stdout = PyObject_CallMethod(io, "StringIO", nullptr);
        PyObject_SetAttrString(sys, "stdout", new_stdout);
        PyRun_SimpleString(full_code.c_str());

        PyObject* output = PyObject_CallMethod(new_stdout, "getvalue", nullptr);
        if (output != nullptr) {
            const char* output_cstr = PyUnicode_AsUTF8(output);
            if (output_cstr) {
                code_output.push_back(std::string(output_cstr));
            }
            Py_DECREF(output);
        }

        executed_code.push_back(code_output);
        Py_DECREF(new_stdout);
    }

    Py_Finalize();

    return executed_code;
}

std::deque<std::string> embed_python_code(std::deque<std::string> lines, const std::vector<std::vector<std::string>>& executed_code) {
    bool in_python_block = false;
    std::deque<std::string> new_lines;
    int executed_code_index = 0;
    for (const std::string& line : lines) {
        if (line.find("<python>") != std::string::npos) {
            in_python_block = true;
            for (const std::string& code_line : executed_code[executed_code_index]) {
                new_lines.push_back(code_line);
            }
            continue;
        }

        if (line.find("</python>") != std::string::npos) {
            in_python_block = false;
            executed_code_index++;
            continue;
        }

        if (!in_python_block) {
            new_lines.push_back(line);

        }
    }
    return new_lines;
}

void html_to_file(const std::deque<std::string>& htmlDeque, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    for (const auto& line : htmlDeque) {
        outFile << line << "\n";
    }
    
    outFile.close();
    if (!outFile) {
        std::cerr << "Error: Failed to write to file " << filename << "." << std::endl;
    }
}




int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <HTML Filename>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        return EXIT_FAILURE;
    }

    std::deque<std::string> lines;
    std::string line;
    while (getline(file, line)) {  
        lines.push_back(line);
    }

    // check that there are valid python tags in the file
    valid_python_tag(lines);
    // next step is to go into the file and parse code inside the python tags
    std::vector<std::vector<std::string>> python_code = parse_python_code(lines);
    std::vector<std::vector<std::string>> executed_code = execute_python_code(python_code);
    std::deque<std::string> embedded_code = embed_python_code(lines, executed_code);
    html_to_file(embedded_code, argv[1]+std::string("_formatted.html"));


    // for (const std::string& line : embedded_code) {
    //     std::cout << line << std::endl;
    // }

    // for (const std::string& line : embedded_code) {
    //     std::cout << line << std::endl;
    // }

    return EXIT_SUCCESS;
}
