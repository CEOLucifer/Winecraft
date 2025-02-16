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
};