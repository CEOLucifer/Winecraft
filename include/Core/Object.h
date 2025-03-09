#pragma once

#include "../Typedef.h"

/// 共享指针托管的对象的类型基类
class Object
{
protected:
    Wp<Object> thisWeak;

public:
    virtual ~Object() = default;

    virtual void OnObjectCreated()
    {}

    void Destroy()
    {
        OnDestroyed();
    }

    virtual void OnDestroyed()
    {
    }

    template<typename T>
    Sp<T> CastTo()
    {
        return std::dynamic_pointer_cast<T>(thisWeak.lock());
    }

    template<typename T>
    Sp<T> StaticCastTo()
    {
        return std::static_pointer_cast<T>(thisWeak.lock());
    }

public:
    template<typename T>
    requires std::is_base_of_v<Object, T>
    static Sp<T> Create()
    {
        Sp<T> This(new T);
        This->thisWeak = This;
        This->OnObjectCreated();
        return This;
    }
};