#pragma once

#include "Core/Component.h"
#include <glm/glm.hpp>

class SpotLight : public Component
{
public:
    glm::vec3 Color = {1, 1, 1};
    glm::vec3 Ambient = {1, 1, 1};

    // 衰减参数：

    float Constant = 1.0;
    float Linear = 0.09;
    float Quadratic = 0.032;

public:
    void Awake() override;
};