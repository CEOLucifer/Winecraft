#pragma once

#include <array>
#include "Block.h"

/// 区块
class Section
{
public:
    std::array<std::array<std::array<Block, 32>, 32>, 32> Blocks ;

public:
    void FillWith(Block block);
};