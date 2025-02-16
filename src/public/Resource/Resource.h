#pragma once

#include "ResourceSystem.h"
#include <string>

/// @brief 资源。用于表示外部文件系统的资源。
/// 
class Resource
{
    template<typename T>
    friend class ResourceFactory;

private:
    /// @brief 资源的路径。用作ResourceSystem中的缓存键。
    std::string path;

public:
    virtual ~Resource() {}

    const std::string& GetPath() { return path; }
};