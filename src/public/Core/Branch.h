#pragma once

#include <list>
#include "Node.h"
#include "Transform.h"
#include "Typedef.h"
#include <glm/glm.hpp>

/// @brief 分支
///
class Branch : public Node, public Transform
{
    friend class CoreSystem;
    friend class Node;

#pragma region 子节点
private:
    // 继承Node而不继承Branch的子结点
    std::list<Sp<Node>> childNodes;

    // 继承Branch的子结点。用于变换。
    std::list<Sp<Branch>> childBranches;
#pragma endregion


private:
    std::list<Sp<Node>> components;

public:
    template <typename T> Sp<T> GetChild()
    {
        for (auto each : components)
        {
            if (Sp<T> target = each->CastTo<T>())
            {
                return target;
            }
        }
        return nullptr;
    }

    template <typename T> Sp<T> GetChildOrAdd()
    {
        Sp<T> node = GetChild<T>();
        if (node == nullptr)
        {
            node = AddNode<T>();
        }
        return node;
    }

    template <typename T> Sp<T> AddNode(std::string _name = "")
    {
        Sp<T> newNode = Node::_createRaw<T>(_name);
        newNode->SetParent(CastTo<Branch>());
        newNode->OnAdded();
        return newNode;
    }

private:
    void _callOnDestroyedOfChildren();

public:
    template <typename T> static Sp<T> Create(std::string _name = "")
    {
        Sp<T> This = _createRaw<T>(_name);
        This->SetParent(CoreSystem::Instance()->root);
        return This;
    }

    static Sp<Branch> Create(std::string _name = "")
    {
        return Create<Branch>();
    }
};