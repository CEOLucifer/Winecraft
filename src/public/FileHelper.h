#pragma once

#include <string>

/// 文件助手类
class FileHelper
{
public:
    /// 读取指定路径文件文本内容
    /// @param filename
    /// @return 文本内容
    static std::string ReadFile(const std::string& path);
};