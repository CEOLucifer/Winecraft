#pragma once

#include "RenderPass.h"

/// 单例渲染通道的基类
/// \tparam T
template<typename T>
class SingletonRenderPass : public RenderPass
{
private:
    static Sp<T> instance;

public:
    static Sp<T> Instance()
    {
        return instance;
    }

    static void LoadInstance()
    {
        instance = Object::NewObject<T>();
    }
};

template<typename T>
Sp<T> SingletonRenderPass<T>::instance = nullptr;