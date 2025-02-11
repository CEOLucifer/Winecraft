#pragma once

/// @brief 单例类基类模板
///
/// @tparam T 子类
template <typename T> class Singleton
{
public:
    virtual void OnLoad() {}

    virtual void OnUnload() {}

private:
    static T* instance;

public:
    static T* LoadInstance()
    {
        if (instance)
            return instance;

        instance = new T;
        instance->OnLoad();
        return instance;
    }

    static T* Instance() { return instance; }

    static void UnloadInstance()
    {
        if (!instance)
            return;

        instance->OnUnload();
        delete instance;
        instance = nullptr;
    }
};

template <typename T> T* Singleton<T>::instance = nullptr;
