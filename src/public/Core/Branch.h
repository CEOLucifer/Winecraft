#pragma once

#include <list>
#include "Node.h"
#include "Typedef.h"
#include <glm/glm.hpp>

/// @brief 分支
///
class Branch : public Node
{
    friend class CoreSystem;
    friend class Node;

#pragma region 变换

public:
    glm::vec3 Position = {0, 0, 0};
    glm::vec3 Rotation = {0, 0, 0};
    glm::vec3 Scale = {1, 1, 1};

private:
    // 继承Node而不继承Branch的子结点
    std::list<Sp<Node>> childNodes;

    // 继承Branch的子结点。用于变换。
    std::list<Sp<Branch>> childBranches;

public:
    glm::vec3 GetForward();

    glm::vec3 GetUp();

    glm::vec3 GetRight();

    glm::mat4 GetRotateMat();

    glm::mat4 GetViewMat();

    glm::mat4 GetModelMat();

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
            node = Node::Create<T>();
            node->SetParent(CastTo<Branch>());
        }
        return node;
    }

private:
    void _callOnDestroyedOfChildren();
};