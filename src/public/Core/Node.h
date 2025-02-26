#pragma once

#include "Typedef.h"
#include "Core/CoreSystem.h"
#include <string>

class Branch;

/// @brief 节点
class Node
{
    friend class CoreSystem;
    friend class Branch;

public:
    std::string name;

protected:
    Wp<Node> thisWeak;

private:
    Wp<Branch> parent;

public:
    template <typename T> Sp<T> CastTo()
    {
        return std::dynamic_pointer_cast<T>(thisWeak.lock());
    }

    virtual void Awake() {}

    virtual void OnAdded() {}

    virtual void Update() {}

    Wp<Branch> GetParent() { return parent; }

    void SetParent(Wp<Branch> value);

public:
    template <typename T> static Sp<T> Create(std::string _name = "")
    {
        Sp<T> This(new T);
        This->thisWeak = This;
        This->name = _name;
        This->SetParent(CoreSystem::Instance()->GetRoot());
        This->Awake();
        return This;
    }
};