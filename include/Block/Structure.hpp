#pragma once

#include "Block/Block.h"
#include "Std/String.h"
#include "Std/Vec.h"

/// @brief 结构
///
class Structure
{
private:
    Vec<Block> blocks;
    u32 mx = 0;
    u32 my = 0;
    u32 mz = 0;

public:
    void SetSize(u32 _x, u32 _y, u32 _z);

    const Vec<Block>& GetBlocks() { return blocks; }

    Block& operator[](u32 _x, u32 _y, u32 _z)
    {
        return blocks[_x * my * mz + _y * mz + _z];
    }

    u32 GetX() { return mx; }

    u32 GetY() { return my; }

    u32 GetZ() { return mz; }

    String Serialize();

    void Deserialize(String jsonStr);
};