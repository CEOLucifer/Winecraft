#pragma once

#include "ResourceSystem.h"
#include "ArduinoJson.h"
#include "Std/SmartPtr.h"
#include "Std/String.h"

/// @brief 资源。用于表示外部文件系统的资源。
class Resource : public Object
{
    friend class ResourceSystem;

private:
    /// @brief 资源的路径。用作ResourceSystem中的缓存键。
    String path;

public:
    const String& GetPath()
    { return path; }

    virtual void OnResourceCreation(const JsonDocument& doc)
    {}

public:
    template<typename T>
    requires std::is_base_of_v<Resource, T>
    static Sp<T> Load(String path)
    {
        return ResourceSystem::Instance()->Load<T>(path);
    }
};