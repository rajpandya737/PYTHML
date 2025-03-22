#include "file.hpp"


std::vector<std::string> File::embed_python_code(std::vector<std::string> lines, const std::vector<std::string>& executed_code) {
    bool in_python_block = false;
    std::vector<std::string> new_lines;
    auto executed_code_it = executed_code.begin();

    for (const std::string& line : lines) {
        std::string lower = line;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower); 
        if (lower.find("<python>") != std::string::npos) {
            in_python_block = true;
            while (executed_code_it != executed_code.end() && (*executed_code_it) != "</python>") {
                new_lines.push_back(*executed_code_it);
                ++executed_code_it;
            }
            continue;
        }

        if (lower.find("</python>") != std::string::npos) {
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

void File::html_to_file(const std::vector<std::string>& htmlVector, const std::string& filename) {
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

std::vector<std::string> File::read_file(int argc, char* argv[]){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <HTML Filename>" << std::endl;
        return {};
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        return {};
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {  
        lines.push_back(line);
    }    

    return lines;
}