#pragma once

#include "../Typedef.h"
#include "CoreSystem.h"
#include "Object.h"
#include <string>

class Branch;

/// @brief 节点。若一个类是Node子类而不是Branch子类。则其只能通过Branch的AddNode方法创建。
class Node : public Object
{
    friend class CoreSystem;

    friend class Branch;

public:
    std::string name;

private:
    // !!!除了根节点，其它节点的parent应该都为null
    Wp<Branch> parent;

    // 在CoreSystem中，nodeVec中的索引。用于快速增删。
    uint32_t index;

    bool isDestroyed = false;

public:
    virtual void Awake()
    {}

    virtual void OnAdded()
    {}

    virtual void Update()
    {}

    /// @brief !!! 严禁调用销毁相关逻辑
    virtual void OnDestroyed()
    {}

    void Destroy();

    Wp<Branch> GetParent()
    { return parent; }

    void SetParent(Wp<Branch> value);

private:
    /// @brief 从旧父结点的子链表中移除
    void _removeFromParent();

private:
    template<typename T>
    static Sp<T> _createRaw(std::string _name = "")
    {
        Sp<T> This = Create<T>();
        This->name = _name;

        // 添加到nodeVec
        CoreSystem::Instance()->nodeVec.push_back(This);
        This->index = CoreSystem::Instance()->nodeVec.size() - 1;
        This->Awake();
        return This;
    }
};