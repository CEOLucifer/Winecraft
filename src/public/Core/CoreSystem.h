#pragma once

#include "Singleton.h"
#include "Typedef.h"

class GameObject;

class CoreSystem : public Singleton<CoreSystem>
{
private:
    Sp<GameObject> root;

public:
    void Update();

    void OnLoad() override;

    Sp<GameObject> GetRoot() { return root; }

private:
    void updateGameObject(Sp<GameObject> gameObject);
};