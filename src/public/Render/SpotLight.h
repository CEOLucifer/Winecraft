#pragma once

#include "Node/Node.h"
#include "Transform.h"

class SpotLight : public Node, public Transform
{
public:
    glm::vec3 Color;
};