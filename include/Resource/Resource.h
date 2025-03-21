#pragma once

#include "ResourceSystem.h"
#include <string>
#include "ArduinoJson.h"
#include "Std/SmartPtr.h"

/// @brief 资源。用于表示外部文件系统的资源。
class Resource : public Object
{
    friend class ResourceSystem;

private:
    /// @brief 资源的路径。用作ResourceSystem中的缓存键。
    std::string path;

public:
    const std::string& GetPath()
    { return path; }

    virtual void OnCreated(const JsonDocument& doc)
    {}

public:
    template<typename T>
    requires std::is_base_of_v<Resource, T>
    static Sp<T> Load(std::string path)
    {
        return ResourceSystem::Instance()->Load<T>(path);
    }
};