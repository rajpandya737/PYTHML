#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <Python.h>
#include <cctype>


bool valid_python_tag(const std::vector<std::string>& lines) {
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

std::vector<std::string> parse_python_code(const std::vector<std::string>& lines) {
    std::vector<std::string> python_code;
    int line_number = 0;

    while (line_number < lines.size()) {
        if (lines[line_number].find("<python>") != std::string::npos) {
            line_number++;
            while (line_number < lines.size() && lines[line_number].find("</python>") == std::string::npos) {
                python_code.push_back(lines[line_number]);
                line_number++;
            }
        }
        line_number++;
    }

    // need to get a way to remove all the starting spaces from the code

    return python_code;
}



std::vector<std::string> execute_python_code(const std::vector<std::string>& python_code) {
    std::vector<std::string> executed_code;

    Py_Initialize();

    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* io = PyImport_ImportModule("io");

    if (!sys || !io) {
        PyErr_Print();
        Py_Finalize();
        return executed_code;
    }

    std::string full_code;
    for (const std::string& line : python_code) {
        full_code += line + "\n";  
    }

    PyObject* new_stdout = PyObject_CallMethod(io, "StringIO", nullptr);
    if (!new_stdout) {
        PyErr_Print();
        Py_Finalize();
        return executed_code;
    }

    PyObject_SetAttrString(sys, "stdout", new_stdout);
    PyRun_SimpleString(full_code.c_str());

    PyObject* output = PyObject_CallMethod(new_stdout, "getvalue", nullptr);
    if (output != nullptr) {
        const char* output_cstr = PyUnicode_AsUTF8(output);
        if (output_cstr) {
            std::string output_str(output_cstr);
            size_t pos = 0;
            while ((pos = output_str.find('\n')) != std::string::npos) {
                executed_code.push_back(output_str.substr(0, pos));
                output_str.erase(0, pos + 1);
            }
            if (!output_str.empty()) {
                executed_code.push_back(output_str);
            }
        }
        Py_DECREF(output);
    }

    Py_DECREF(new_stdout);
    Py_Finalize();

    return executed_code;
}


std::vector<std::string> embed_python_code(std::vector<std::string> lines, const std::vector<std::string>& executed_code) {
    bool in_python_block = false;
    std::vector<std::string> new_lines;
    auto executed_code_it = executed_code.begin();

    for (const std::string& line : lines) {
        if (line.find("<python>") != std::string::npos) {
            in_python_block = true;
            while (executed_code_it != executed_code.end() && (*executed_code_it) != "</python>") {
                new_lines.push_back(*executed_code_it);
                ++executed_code_it;
            }
            continue;
        }

        if (line.find("</python>") != std::string::npos) {
            in_python_block = false;
            if (executed_code_it != executed_code.end()) {
                ++executed_code_it;
            }
            continue;
        }

        if (!in_python_block) {
            new_lines.push_back(line);
        }
    }

    return new_lines;
}



void html_to_file(const std::vector<std::string>& htmlVector, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    for (const auto& line : htmlVector) {
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

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {  
        lines.push_back(line);
    }    

    // check that there are valid python tags in the file
    valid_python_tag(lines);
    // next step is to go into the file and parse code inside the python tags
    std::vector<std::string> python_code = parse_python_code(lines);
    std::vector<std::string> executed_code = execute_python_code(python_code);
    std::vector<std::string> embedded_code = embed_python_code(lines, executed_code);
    html_to_file(embedded_code, argv[1]+std::string("_formatted.html"));


    // for (const std::string& line : embedded_code) {
    //     std::cout << line << std::endl;
    // }

    // for (const std::string& line : embedded_code) {
    //     std::cout << line << std::endl;
    // }

    return EXIT_SUCCESS;
}
