#pragma once

#include "Node.h"
#include "Transform.h"
#include "Std/SmartPtr.h"
#include "glm/glm.hpp"
#include "Std/List.h"

/// @brief 分支
///
class Branch : public Node, public Transform
{
    friend class CoreSystem;

    friend class Node;

private:
    // 继承Node而不继承Branch的子结点
    List<Sp<Node>> childNodes;

    // 继承Branch的子结点。用于父子空间变换。
    List<Sp<Branch>> childBranches;


public:
    /// 获取指定类型的子结点
    /// \tparam T
    /// \return
    template<typename T>
    requires std::is_base_of_v<Node, T>
    Sp<T> GetChild()
    {
        for (auto each: childNodes)
        {
            if (Sp<T> target = each->CastTo<T>())
            {
                return target;
            }
        }
        for (auto each: childBranches)
        {
            if (Sp<T> target = each->CastTo<T>())
            {
                return target;
            }
        }
        return nullptr;
    }

    /// 获取指定类型的子结点，若不存在，则添加一个此节点并返回。
    /// \tparam T
    /// \return
    template<typename T>
    requires std::is_base_of_v<Node, T>
    Sp<T> GetChildOrAdd()
    {
        Sp<T> node = GetChild<T>();
        if (node == nullptr)
        {
            node = AddNode<T>();
        }
        return node;
    }

    /// 添加一个子结点。类似Unity的AddComponent。
    /// \tparam T
    /// \param _name
    /// \return
    template<typename T>
    requires std::is_base_of_v<Node, T>
    Sp<T> AddNode(String _name = "")
    {
        Sp<T> newNode = Node::_newRawNode<T>(_name);
        newNode->SetParent(CastTo<Branch>());
        newNode->OnAdded();
        return newNode;
    }

    const List<Sp<Node>>& GetChildNodes()
    {
        return childNodes;
    }

    const List<Sp<Branch>>& GetChildBranches()
    {
        return childBranches;
    }

private:
    void _callOnNodeDestroyedOfChildren();

public:
    /// 创建指定子类的Branch
    /// \tparam T
    /// \param _name
    /// \return
    template<typename T>
    requires std::is_base_of_v<Branch, T>
    static Sp<T> NewBranch(String _name = "")
    {
        Sp<T> This = _newRawNode<T>(_name);
        This->SetParent(CoreSystem::Instance()->root);
        return This;
    }

    /// 创建空Branch对象
    /// \param _name
    /// \return
    static Sp<Branch> NewBranch(String _name = "")
    {
        return NewBranch<Branch>(_name);
    }
};