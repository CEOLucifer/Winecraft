#pragma once

#include <memory>
#include <string>
#include "ResourceSystem.h"
#include <iostream>

template <typename T> class ResourceFactory
{
public:
    std::shared_ptr<T> Create(std::string path)
    {
        auto _res = LoadFromCache(path);
        if (_res)
        {
            std::cout << "found resource cached, path:" + path << std::endl;
            return std::dynamic_pointer_cast<T>(_res);
        }
        else
        {
            std::shared_ptr<T> t(new T);
            t->path = path;
            onCreate(t, path);
            ResourceSystem::Instance()->Cache(t);
            return t;
        }
    }

    void Cache(std::shared_ptr<T> res)
    {
        ResourceSystem::Instance()->Cache(res);
    }

    std::shared_ptr<T> LoadFromCache(std::string path)
    {
        return std::dynamic_pointer_cast<T>(
            ResourceSystem::Instance()->Get(path));
    }

protected:
    virtual void onCreate(std::shared_ptr<T> res, std::string path) {}
};