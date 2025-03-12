#pragma once

#include <array>
#include "Block.h"
#include <glm/glm.hpp>

/// 区块
class Section
{
public:
    static constexpr uint32_t Size = 32;
    static constexpr uint32_t Height = 32;

public:
    std::array<std::array<std::array<Block, Size>, Height>, Size> Blocks;

    /// 世界坐标
    glm::vec3 Coords;

    /// 四角顶点生成高度。用于双线性插值，生成地形。
    float verticeHeights[4];

public:
    void FillWith(Block block);
};