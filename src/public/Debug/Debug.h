#pragma once

#include "Debugable.h"
#include <iostream>

class Debug
{
public:
    static void Log(const Debugable& debugable)
    {
        std::cout << debugable.info << std::endl;
    }

    static void Log(const std::string& info) { std::cout << info << std::endl; }

    static void LogWarning(const std::string& info)
    {
        std::cout << std::format("\033[0m\033[33m{}\033[0m", info) << std::endl;
    }

    static void LogError(const std::string& info)
    {
        std::cout << std::format("\033[0m\033[31m{}\033[0m", info) << std::endl;
    }
};