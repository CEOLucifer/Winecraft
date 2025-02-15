#pragma once

#include "Singleton.h"
#include <memory>
#include <string>
#include <unordered_map>

class Resource;

class ResourceSystem : public Singleton<ResourceSystem>
{
private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> resMap;

public:
    std::shared_ptr<Resource> Get(std::string path)
    {
        if (resMap.contains(path))
        {
            return resMap[path];
        }
        return nullptr;
    }

    void Cache(std::shared_ptr<Resource> res);
};