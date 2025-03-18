#pragma once

#include "Std/Basic.h"


/// 方块
class Block
{
public:
    /// 0 表示无方块
    u32 id = 0;

public:
    Block() = default;

    Block(u32 id)
    {
        this->id = id;
    }
};