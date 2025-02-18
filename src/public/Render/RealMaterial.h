#pragma once

#include "Material.h"

/// @brief 现实材质
///
class RealMaterial : public Material
{
public:
    std::shared_ptr<Texture> diffuseTex;
    std::shared_ptr<Texture> specularTex;
    float shininess = 32.0;

public:
    void OnUpdateShaderProgram(Camera& camera) override;
};