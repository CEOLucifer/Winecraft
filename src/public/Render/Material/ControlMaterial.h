#pragma once

#include "Render/Material/Material.h"

class ControlMaterial : public Material
{
public:
    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};