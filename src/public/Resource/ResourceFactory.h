#pragma once

#include <memory>
#include <string>
#include "ResourceSystem.h"
#include <iostream>

/// @brief 资源工厂。由 具体资源类 的工厂类继承。
/// 
/// @tparam T 
template <typename T> class ResourceFactory
{
public:
    /// @brief 创建一个资源。如果已缓存，则取缓存。 
    /// 
    /// @param path 
    /// @return std::shared_ptr<T> 
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

    /// @brief 缓存 
    /// 
    /// @param res 
    void Cache(std::shared_ptr<T> res)
    {
        ResourceSystem::Instance()->Cache(res);
    }

    /// @brief 从缓存中加载 
    /// 
    /// @param path 
    /// @return std::shared_ptr<T> 
    std::shared_ptr<T> LoadFromCache(std::string path)
    {
        return std::dynamic_pointer_cast<T>(
            ResourceSystem::Instance()->Get(path));
    }

protected:
    /// @brief 当该资源不在缓存中时，如何真实地新建一个该资源？ 
    /// 
    /// @param res 
    /// @param path 
    virtual void onCreate(std::shared_ptr<T> res, std::string path) {}
};