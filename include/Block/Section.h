#pragma once

#include <array>
#include "Block.h"
#include "../Typedef.h"
#include "../Render/Vertex.h"

class ShaderProgram;
class Camera;

/// 区块
class Section
{
private:
    std::array<std::array<std::array<Block, 32>, 32>, 32> blocks = {};

    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    uint32_t instance_vbo = 0;

    Sp<ShaderProgram> shaderProgram;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

public:
    void Draw(Sp<Camera> camera);

public:
    static Section New();
};