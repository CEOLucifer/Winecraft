#include "FileHelper.h"

#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Debug/Debug.h"

using namespace std;

String FileHelper::ReadFile(const String& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        Debug::LogWarning(format("Failed to open file: {}", path));
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void FileHelper::WriteFile(const String& path, const String& content)
{
    // 使用 std::ofstream 写入文件
    std::ofstream file(
        path, std::ios::out | std::ios::trunc); // std::ios::trunc 表示覆盖模式
    if (!file.is_open())
    {
        Debug::LogWarning(format("Failed to open file for writing: {}", path));
        return;
    }

    file << content; // 将内容写入文件
    if (file.fail()) // 检查写入是否成功
    {
        Debug::LogWarning(format("Failed to write content to file: {}", path));
    }

    file.close(); // 关闭文件
}
