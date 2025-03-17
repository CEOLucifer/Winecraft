#pragma once

#include <array>
#include "Block.h"
#include <glm/glm.hpp>

/// 区块
class Section
{
public:
    static constexpr uint32_t Size = 16;
    static constexpr uint32_t Height = 128;

public:
    std::array<std::array<std::array<Block, Size>, Height>, Size> Blocks;

    /// 世界坐标
    glm::vec3 Coords;

public:
    void FillWith(Block block);
};