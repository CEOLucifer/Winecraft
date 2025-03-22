#pragma once

#include "Std/SmartPtr.h"
#include "CoreSystem.h"
#include "Object.h"
#include "Std/String.h"
#include "Std/Basic.h"

class Branch;

/// @brief 节点。
class Node : public Object
{
    friend class CoreSystem;
    friend class Branch;

public:
    String name;

private:
    // !!!除了根节点，其它节点的parent应该都为null
    Wp<Branch> parent;

    // 在CoreSystem中，nodeVec中的索引。用于快速增删。
    u32 index;

    // 是否已经被标记删除？
    // 若为true，则在nodeVec遍历过程中被加入removingNodes，在node遍历结束后，从nodeVec中移除。
    bool isDestroyed = false;

public:
    virtual void Awake()
    {}

    virtual void OnAdded()
    {}

    virtual void Update()
    {}

    /// 销毁此节点
    void DestroyNode();

    /// 由子类重写。
    virtual void OnNodeDestroyed()
    {}

    Wp<Branch> GetParent()
    { return parent; }

    void SetParent(Wp<Branch> value);

private:
    /// @brief 从旧父结点的子链表中移除
    void _removeFromParent();

public:
    /// 创建一个节点。父结点被设置为根节点。
    /// \tparam T
    /// \param _name
    /// \return
    template<typename T>
    requires std::is_base_of_v<Node,T>
    static Sp<T> NewNode(String _name = "")
    {
        Sp<T> This = _newRawNode<T>(_name);
        This->SetParent(CoreSystem::Instance()->root);
        return This;
    }

private:
    template<typename T>
    requires std::is_base_of_v<Node, T>
    static Sp<T> _newRawNode(String _name = "")
    {
        Sp<T> This = NewObject<T>();
        This->name = _name;

        // 添加到nodeVec
        CoreSystem::Instance()->addingNodes.push_back(This);
        This->Awake();
        return This;
    }
};