#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Std/Map.h"
#include "Std/Basic.h"

/// 字形
class Character
{
public:

    /// 字形纹理的ID。每个字形都有自己的gl纹理
    u32 TextureID;

    /// 字形大小
    glm::ivec2 Size;

    /// 从基准线到字形左部/顶部的偏移值
    glm::ivec2 Bearing;

    /// 原点距下一个字形原点的距离
    i32 Advance;
};

