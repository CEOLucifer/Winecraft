#include "Core/GameObject.h"
#include "Core/Component.h"
#include "Core/CoreSystem.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 GameObject::GetViewMat()
{
    glm::mat4 view;

    glm::vec3 lookDir = GetForward();
    glm::vec3 up = GetUp();

    view = glm::lookAt(Position, Position + lookDir, up);
    return view;
}

glm::vec3 GameObject::GetForward()
{
    glm::vec3 forward;
    forward = GetRotateMat() * glm::vec4(0, 0, -1, 0);
    return forward;
}

glm::vec3 GameObject::GetUp()
{
    glm::vec3 up;
    up = GetRotateMat() * glm::vec4(0, 1, 0, 0);
    return up;
}

glm::vec3 GameObject::GetRight()
{
    glm::vec3 right;
    right = GetRotateMat() * glm::vec4(1, 0, 0, 0);
    return right;
}

glm::mat4 GameObject::GetRotateMat()
{
    glm::mat4 rotate = {1};
    // 直接在一个矩阵上应用所有旋转
    rotate = glm::rotate(rotate, glm::radians(Rotation.y),
                         glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(Rotation.x),
                         glm::vec3(1.0f, 0.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(Rotation.z),
                         glm::vec3(0.0f, 0.0f, 1.0f));
    return rotate;
}


glm::mat4 GameObject::GetModelMat()
{
    // 初始化模型矩阵为单位矩阵
    glm::mat4 model = glm::mat4(1.0f);
    // 应用平移
    model = glm::translate(model, Position);
    // 直接在一个矩阵上应用所有旋转
    model = glm::rotate(model, glm::radians(Rotation.y),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(Rotation.x),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(Rotation.z),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    // 应用缩放
    model = glm::scale(model, Scale);
    return model;
}

void GameObject::SetParent(Sp<GameObject> value)
{
    Sp<GameObject> oldParent = parent.lock();

    if (oldParent)
    {
        auto& children = oldParent->children;
        children.erase(
            std::remove(children.begin(), children.end(), weak.lock()),
            children.end());
    }

    parent = value;

    if (value)
    {
        value->children.push_back(weak.lock());
    }
}




void GameObject::AddComponent(Sp<Component> component)
{
    auto gameObject = component->gameObject.lock();
    if (gameObject.get() == this)
    {
        return;
    }

    components.push_back(component);
    component->gameObject = weak;
}

void GameObject::RemoveComponent(Sp<Component> component)
{
    auto gameObject = component->gameObject.lock();

    if (gameObject.get() != this)
    {
        return;
    }

    components.erase(
        std::remove(components.begin(), components.end(), component));
    component->gameObject.reset();
}


Sp<GameObject> GameObject::Create()
{
    Sp<GameObject> This(new GameObject);
    This->weak = This;
    This->SetParent(CoreSystem::Instance()->GetRoot());
    return This;
}