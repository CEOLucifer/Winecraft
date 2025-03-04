#pragma once

#include "Material.h"
#include "Typedef.h"

class Texture;
class Renderer;

/// @brief 真实材质
///
class RealMaterial : public Material
{
public:
    Sp<Texture> diffuseTex;
    Sp<Texture> specularTex;
    float shininess = 32.0;

public:
    void OnCreated(const JsonDocument &doc) override;


    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};