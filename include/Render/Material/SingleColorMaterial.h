#pragma once

#include "Material.h"
#include "glm/glm.hpp"

/// @brief 单色材质
///
class SingleColorMaterial : public Material
{
public:
    glm::vec3 Color = glm::vec3(1.0f);

public:
    void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) override;
};