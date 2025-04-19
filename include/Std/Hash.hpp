#pragma once

#include <unordered_map>
#include "Std/Basic.h"
#include "Std/Math.h"

template<>
struct std::hash<i32vec2>
{
    std::size_t operator()(const i32vec2& p) const
    {
        // 通过位运算和异或操作组合两个哈希值
        return p.x + (p.y << sizeof(u32));
    }
};