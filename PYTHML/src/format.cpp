#include "format.hpp"
#include <iostream>

const char* Formatter::flatten_vector_to_string(const std::vector<std::string>& input_html) {
    static std::string result;  
    result.clear();  

    for (const auto& str : input_html) {
        result += str;
    }
    return result.c_str();  
}




const std::vector<std::string> Formatter::format_html(const std::vector<std::string>& input_html) {
    
    const char* input = flatten_vector_to_string(input_html);
    
    // Initialize the Tidy document and buffer
    TidyDoc tdoc = tidyCreate();
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};

    // Parse and tidy the input HTML
    tidyOptSetInt(tdoc, TidyIndentContent, TidyAutoState);  
    tidyOptSetInt(tdoc, TidyIndentSpaces, 2); 

    if (tidyParseString(tdoc, input) >= 0) {
        tidyCleanAndRepair(tdoc);
        tidySaveBuffer(tdoc, &output);
    }

    // Convert the Tidy output buffer into a string
    std::string formattedHtml(reinterpret_cast<char*>(output.bp), output.size);

    std::cout << output.bp;

    // Clean up
    tidyRelease(tdoc);
    tidyBufFree(&output);
    
    std::vector<std::string> result;
    size_t pos = 0;
    while ((pos = formattedHtml.find('\n')) != std::string::npos) {
        result.push_back(formattedHtml.substr(0, pos));
        formattedHtml.erase(0, pos + 1);
    }
    if (!formattedHtml.empty()) {
        result.push_back(formattedHtml);
    }

    return result;

}
