#pragma once

#include "Singleton.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "Std/SmartPtr.h"
#include "FileHelper.h"
#include "Debug/Debug.h"
#include "Creator.h"
#include "ArduinoJson.h"

class Resource;

class BaseCreator;

/// @brief 资源系统
///
class ResourceSystem : public Singleton<ResourceSystem>
{
private:
    /// @brief 资源的缓存map。
    ///
    std::unordered_map<std::string, Sp<Resource>> resMap;

    /// @brief
    /// 存储类名到对应的Creator的映射。这样通过json文件中的className找到对应Creator。
    std::unordered_map<std::string, Up<BaseCreator>> creatorMap;

public:
    void OnLoad() override;

    /// @brief 获取指定路径资源的缓存
    ///
    /// @param path
    /// @return Sp<Resource>
    Sp<Resource> Get(const std::string& path)
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
    void Cache(Sp<Resource> res);

    void RegisterAllResources();

    template <typename T>
        requires std::is_base_of_v<Resource, T>
    void RegisterResource(const std::string& name)
    {
        Up<Creator<T>> newLoader(new Creator<T>);
        creatorMap.insert({name, std::move(newLoader)});
    }

    /// 加载指定类型的资源
    /// \tparam T
    /// \param path
    /// \return
    template <typename T>
        requires std::is_base_of_v<Resource, T>
    Sp<T> Load(const std::string& path)
    {
        // 尝试从缓存中获取
        auto _res = std::dynamic_pointer_cast<T>(Get(path));
        if (_res)
        {
            // 已缓存
            // Debug::Log(format("found resource cached, path:{}", path));
            return _res;
        }
        else
        {
            // 新建
            std::string str = FileHelper::ReadFile(path);
            JsonDocument doc;
            deserializeJson(doc, str);
            std::string className = doc["className"];

            if (!creatorMap.contains(className))
            {
                Debug::LogWarning(std::format(
                    "failed to find loader for class {}", className));
                return nullptr;
            }
            else
            {
                // 运用Creator创建资源
                BaseCreator* creator = creatorMap[className].get();
                Sp<Resource> baseRes = creator->CreateNew(doc);
                Sp<T> res = std::dynamic_pointer_cast<T>(baseRes);
                res->path = path;
                Cache(res);
                return res;
            }
        }
    }
};