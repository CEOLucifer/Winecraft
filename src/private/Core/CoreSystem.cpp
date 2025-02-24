#include "Core/CoreSystem.h"
#include "Core/Component.h"
#include "Core/GameObject.h"

void CoreSystem::Update()
{
    if (!root)
        return;
    updateGameObject(root);
}

void CoreSystem::OnLoad() { root = GameObject::Create(); }

void CoreSystem::updateGameObject(Sp<GameObject> gameObject)
{
    if (!gameObject)
        return;

    // Update Component
    for (Sp<Component> each : gameObject->components)
    {
        each->Update();
    }

    // 递归地更新子对象
    for (Sp<GameObject> each : gameObject->children)
    {
        updateGameObject(each);
    }
}
