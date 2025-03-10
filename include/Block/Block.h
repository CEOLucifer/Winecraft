#pragma once

#include <cstdint>

/// 方块
class Block
{
public:
    /// 0 表示无方块
    uint32_t id = 0;

public:
    Block() = default;

    Block(int id)
    {
        this->id = id;
    }
};