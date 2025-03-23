#pragma once

/**
 * @file runner.hpp
 * @author Raj Pandya
 * @brief This class runs and executes the Python code
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <vector>
#include <iostream>
#include <Python.h>


class Runner{
public:
    std::vector<std::string> execute_python_code(const std::vector<std::string>&);
};