#pragma once

#include "CoreSystem.h"
#include "Typedef.h"

class GameObject;
class Transform;

class Component
{
    friend class CoreSystem;
    friend class GameObject;

protected:
    Wp<Component> weak;

private:
    Wp<GameObject> gameObject;

public:
    template <typename T> Sp<T> CastTo()
    {
        return std::dynamic_pointer_cast<T>(weak.lock());
    }

    virtual void Awake() {}

    virtual void Update() {}

    Sp<GameObject> GetGameObject() { return gameObject.lock(); }

public:
    template <typename T> static Sp<T> Create()
    {
        Sp<T> This(new T);
        This->weak = This;
        This->Awake();
        return This;
    }
};