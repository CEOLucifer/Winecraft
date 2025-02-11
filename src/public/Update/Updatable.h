#pragma once

#include "UpdateSystem.h"
#include <memory>

class Updatable
{
public:
    virtual void Update(float deltaTime) {};

public:
    template <typename T> static std::shared_ptr<T> Create()
    {
        std::shared_ptr<T> This(new T);
        This->Init();
        UpdateSystem::Instance()->Add(This);
        return This;
    }
};