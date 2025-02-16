#pragma once

#include "Node/Node3D.h"

class SpotLight : public Node3D
{
public:
    glm::vec3 Color;
    glm::vec3 Ambient = {1, 1, 1};

public:
    void OnInit() override;
};