#pragma once

#include "Node/Node3D.h"

class SpotLight : public Node3D
{
public:
    glm::vec3 Color;

public:
    void Init() override;
};