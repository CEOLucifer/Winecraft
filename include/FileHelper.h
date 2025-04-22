#pragma once

#include "Std/String.h"

/// 文件助手类
class FileHelper
{
public:
    /// 读取指定路径文件文本内容
    /// @param filename
    /// @return 文本内容
    static String ReadFile(const String& path);

    static void WriteFile(const String& path, const String& content);
};