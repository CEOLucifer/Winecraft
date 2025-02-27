#pragma once

#include "glm/glm.hpp"

class Vertex1
{
public:
    glm::vec3 Position;

public:
    Vertex1() {};
    Vertex1(glm::vec3 _position) : Position(_position) {}
    Vertex1(float x, float y, float z) : Position(x, y, z) {}
};