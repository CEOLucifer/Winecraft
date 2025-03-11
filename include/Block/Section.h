#pragma once

#include <array>
#include "Block.h"

/// 区块
class Section
{
public:
    static constexpr uint32_t Size = 32;
    static constexpr uint32_t Height = 32;

public:
    std::array<std::array<std::array<Block, Size>, Height>, Size> Blocks;

public:
    void FillWith(Block block);
};