#pragma once

#include "Render/Material/Material.h"
#include "Texture.h"

class ControlMaterial : Material
{
public:
    Sp<Texture> texture;

public:
    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};