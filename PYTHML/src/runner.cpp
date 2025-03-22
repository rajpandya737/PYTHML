#include "runner.hpp"

std::vector<std::string> Runner::execute_python_code(const std::vector<std::string>& python_code) {
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