#pragma once

#include "Std/SmartPtr.h"

/// 共享指针托管的对象的类型基类
class Object
{
protected:
    /// 指向本对象的弱指针，用于在成员函数中进行类型转换
    Wp<Object> thisWeak;

public:
    virtual ~Object() = default;

    /// 由子类重写
    virtual void OnObjectCreated()
    {}

    /// 销毁此对象
    void Destroy()
    {
        OnDestroyed();
    }

    /// 由子类重写
    virtual void OnDestroyed()
    {
    }

    /// 转型为指定类型
    /// \tparam T
    /// \return
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
    static Sp<T> NewObject()
    {
        Sp<T> This(new T);
        This->thisWeak = This;
        This->OnObjectCreated();
        return This;
    }
};