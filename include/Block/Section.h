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



    Sp<ShaderProgram> shaderProgram;



public:
    void Draw(Sp<Camera> camera);

public:
    static Section New();
};