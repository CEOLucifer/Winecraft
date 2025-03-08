#include "../include/FileHelper.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string FileHelper::ReadFile(const string& path)
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
