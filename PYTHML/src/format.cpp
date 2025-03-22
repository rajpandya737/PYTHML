#include "format.hpp"

const char* flattenVectorToString(const std::vector<std::string>& inputHtml) {
    static std::string result;  
    result.clear();  

    for (const auto& str : inputHtml) {
        result += str;
    }
    return result.c_str();  
}


std::vector<std::string> tidyBufferToVector(const TidyBuffer& buffer) {
    std::vector<std::string> result;
    const char* content = (const char*)buffer.bp;
    
    std::string line;
    
    for (size_t i = 0; content[i] != '\0'; ++i) {
        if (content[i] == '\n') {
            result.push_back(line);
            line.clear();
        } else {
            line.push_back(content[i]);
        }
    }

    if (!line.empty()) {
        result.push_back(line);
    }

    return result;
}


const std::vector<std::string> formatHTML(const std::vector<std::string>& inputHtml) {
    
    const char* input = flattenVectorToString(inputHtml);
    
    // Initialize the Tidy document and buffer
    TidyDoc tdoc = tidyCreate();
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};

    // // Set tidy options for indentation (for example, indent size of 2 spaces)
    // Set only indentation options, disable everything else
    // tidyOptSetBool(tdoc, TidyMakeBare, yes);  // Do not add DOCTYPE or extra elements
    // tidyOptSetBool(tdoc, TidyMark, no);       // Do not add the <meta> tag
    // tidyOptSetBool(tdoc, TidyMetaCharset, no); // Do not add charset meta tag
    // tidyOptSetBool(tdoc, TidyMakeClean, no);  // Do not clean or transform content
    // tidyOptSetBool(tdoc, TidyEscapeCdata, no); // Do not escape CDATA sections
    // tidyOptSetBool(tdoc, TidyFixBackslash, no); // Do not fix backslashes in URLs
    // tidyOptSetBool(tdoc, TidyFixComments, no); // Do not fix comment hyphens
    // tidyOptSetBool(tdoc, TidyEscapeScripts, no); // Do not escape scripts
    // tidyOptSetBool(tdoc, TidyIndentAttributes, no); // Do not indent attributes
    // tidyOptSetBool(tdoc, TidyIndentCdata, no);    // Do not indent CDATA sections
    // tidyOptSetBool(tdoc, TidyIndentContent, no);  // Do not indent content
    // tidyOptSetBool(tdoc, TidyIndentSpaces, yes);  // Enable indentation with spaces
    // tidyOptSetBool(tdoc, TidyIndentAttributes, yes);  // Indent attributes (optional)
    // tidyOptSetInt(tdoc, TidyIndentSpaces, 0);          // Set indentation size to 2 spaces
    
    // Parse the input HTML string into the Tidy document
    
    // Set Tidy options for pretty printing
    // tidyOptSetBool(tdoc, TidyIndentContent, yes);
    // tidyOptSetInt(tdoc, TidyIndentSpaces, 4);  // Indent with 4 spaces
    // tidyOptSetBool(tdoc, TidyXmlOut, no);      // Ensure HTML output
    // tidyOptSetBool(tdoc, TidyQuiet, yes);
    // tidyOptSetBool(tdoc, TidyForceOutput, yes);

    // Parse and tidy the input HTML
    if (tidyParseString(tdoc, input) >= 0) {
        tidyCleanAndRepair(tdoc);
        tidySaveBuffer(tdoc, &output);
    }

    // Convert the Tidy output buffer into a string
    std::string formattedHtml(reinterpret_cast<char*>(output.bp), output.size);

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
