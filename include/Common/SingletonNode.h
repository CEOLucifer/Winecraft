#pragma once

#include "Core/Node.h"

template<typename T>
class SingletonNode : public Node
{
public:
    void Awake() override
    {
        if (instance)
        {
            UnloadInstance();
        }
        instance = CastTo<T>();
    }

private:
    static Sp<T> instance;

public:
    static T& GetInstance()
    {
        return *instance;
    }

    static void UnloadInstance()
    {
        if (!instance)
        {
            return;
        }

        instance->DestroyNode();
        instance = nullptr;
    }
};

template<typename T>
Sp<T> SingletonNode<T>::instance = nullptr;