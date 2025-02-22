#pragma once

#include <glm/glm.hpp>

/// @brief 顶点
///
class Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;

public:
    Vertex() {}
    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoord)
        : Position(pos), Normal(normal), TexCoord(texCoord)
    {}
};