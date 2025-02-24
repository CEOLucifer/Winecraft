#pragma once

#include <vector>
#include "Component.h"
#include "Typedef.h"
#include <glm/glm.hpp>

class GameObject
{
    friend class CoreSystem;

#pragma region 变换

public:
    glm::vec3 Position = {0, 0, 0};
    glm::vec3 Rotation = {0, 0, 0};
    glm::vec3 Scale = {1, 1, 1};

private:
    Wp<GameObject> parent;
    std::vector<Sp<GameObject>> children;

public:
    glm::vec3 GetForward();

    glm::vec3 GetUp();

    glm::vec3 GetRight();

    glm::mat4 GetRotateMat();

    glm::mat4 GetViewMat();

    glm::mat4 GetModelMat();

    void SetParent(Sp<GameObject> value);

#pragma endregion


private:
    std::vector<Sp<Component>> components;
    Wp<GameObject> weak;

public:
    template <typename T> Sp<T> GetComponent()
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

    void AddComponent(Sp<Component>);

    void RemoveComponent(Sp<Component>);

public:
    static Sp<GameObject> Create();
};