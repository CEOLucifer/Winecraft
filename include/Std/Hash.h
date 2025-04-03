#pragma once

#include <unordered_map>
#include "Std/Math.h"

template<>
struct std::hash<i32vec2>
{
    std::size_t operator()(const i32vec2& p) const
    {
        // 使用 std::hash 对 x 和 y 分别计算哈希值，然后进行组合
        auto hashX = std::hash<int>{}(p.x);
        auto hashY = std::hash<int>{}(p.y);
        // 通过位运算和异或操作组合两个哈希值
        return hashX ^ (hashY << 1);
    }
};