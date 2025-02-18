#pragma once

#include "Material.h"
#include <glm/glm.hpp>

/// @brief 单色材质
/// 
class SingleColorMaterial : public Material
{
public:
    glm::vec4 Color;
};