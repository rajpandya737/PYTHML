#pragma once

#include <vector>
#include <iostream>
#include <Python.h>


class Runner{
public:
    std::vector<std::string> execute_python_code(const std::vector<std::string>&);
};