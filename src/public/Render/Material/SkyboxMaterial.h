#pragma once

#include "Material.h"
#include "Typedef.h"

class Texture;
class Renderer;

class SkyboxMaterial : public Material
{
public:
    Sp<Texture> cubeTexture;

public:
    void OnInit() override;

    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};