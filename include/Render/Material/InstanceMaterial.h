#pragma once

#include "../../Core/Transform.h"
#include "Material.h"


class Texture;

/// @brief 实例化材质。可以对物体进行GPU实例化
class InstanceMaterial : public Material
{
public:
    std::vector<Transform> transforms;

    Sp<Texture> diffuseTex;
    Sp<Texture> specularTex;
    float shininess = 32.0;

public:
    void OnCreated(const JsonDocument& doc) override;

    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};