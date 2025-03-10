#pragma once

#include <array>
#include "Block.h"

/// 区块
class Section
{
private:
    std::array<std::array<std::array<Block, 32>, 32>, 32> blocks = {};

public:
    void FillWith(Block block);
};