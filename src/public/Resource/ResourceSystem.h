#pragma once

#include "Singleton.h"
#include <memory>
#include <string>
#include <unordered_map>

class Resource;

/// @brief 资源系统
/// 
class ResourceSystem : public Singleton<ResourceSystem>
{
private:
    /// @brief 资源的缓存map。 
    /// 
    std::unordered_map<std::string, std::shared_ptr<Resource>> resMap;

public:
    /// @brief 获取指定路径资源的缓存 
    /// 
    /// @param path 
    /// @return std::shared_ptr<Resource> 
    std::shared_ptr<Resource> Get(std::string path)
    {
        if (resMap.contains(path))
        {
            return resMap[path];
        }
        return nullptr;
    }

    /// @brief 缓存指定资源 
    /// 
    /// @param res 
    void Cache(std::shared_ptr<Resource> res);
};