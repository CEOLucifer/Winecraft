#pragma once

#include "Typedef.h"
#include "Core/CoreSystem.h"
#include <string>

class Branch;

/// @brief 节点。不允许直接创建非Branch子类。只能通过Branch的AddNode方法创建。
class Node
{
    friend class CoreSystem;
    friend class Branch;

public:
    std::string name;

protected:
    Wp<Node> thisWeak;

private:
    // !!!除了根节点，其它节点的parent应该都为null
    Wp<Branch> parent;

    // 在CoreSystem中，nodeVec中的索引。用于快速增删。
    uint32_t index;

    bool isDestroyed = false;

public:
    template <typename T> Sp<T> CastTo()
    {
        return std::dynamic_pointer_cast<T>(thisWeak.lock());
    }

    virtual void Awake() {}

    virtual void OnAdded() {}

    virtual void Update() {}

    /// @brief !!! 严禁实现销毁
    virtual void OnDestroyed() {}

    void Destroy();

    Wp<Branch> GetParent() { return parent; }

    void SetParent(Wp<Branch> value);

private:
    /// @brief 从旧父结点的子链表中移除
    void _removeFromParent();

private:
    template <typename T> static Sp<T> _createRaw(std::string _name = "")
    {
        Sp<T> This(new T);
        This->thisWeak = This;
        This->name = _name;

        // 添加到nodeVec
        CoreSystem::Instance()->nodeVec.push_back(This);
        This->index = CoreSystem::Instance()->nodeVec.size() - 1;
        This->Awake();
        return This;
    }
};