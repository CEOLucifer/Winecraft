#pragma once

#include <array>
#include "Block.h"
#include "Aggre/Array.h"
#include <glm/glm.hpp>

/// 区块
class Section
{
public:
    static constexpr u32 Size = 16;
    static constexpr u32 Height = 128;

public:
    Array<Array<Array<Block, Size>, Height>, Size> Blocks;

    /// 世界坐标
    glm::vec3 Coords;

public:
    void FillWith(Block block);
};