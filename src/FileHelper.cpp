#include "FileHelper.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

String FileHelper::ReadFile(const String& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}
