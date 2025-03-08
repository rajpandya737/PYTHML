#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <HTML Filename>" << endl;
        return EXIT_FAILURE;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return EXIT_FAILURE;
    }

    deque<string> lines;
    string line;
    while (getline(file, line)) {  
        lines.push_back(line);
    }

    cout<< "HTML File Contents: " << endl;
    cout << lines[0] << endl;
    

    cout << "Correct Usage" << endl;
    return EXIT_SUCCESS;
}
