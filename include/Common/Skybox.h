#pragma once

#include "Core/Node.h"

class Texture;

/// 天空盒节点
class Skybox : public Node
{
private:
    Sp<Texture> skyboxCubeMap;

public:
    void Awake() override;

    void SetCubeMap(Sp<Texture> value)
    {
        skyboxCubeMap = value;
    }

    Sp<Texture> GetCubeMap()
    {
        return skyboxCubeMap;
    }
};