#pragma once

#include "Std/Basic.h"
#include "Std/Math.h"

class WorldInfo
{
public:
    static u32 GetHeight(i32vec2 bwc);

    static f32 GetTemperature(i32vec2 bwc);

    static f32 GetTreeRate(i32vec2 bwc);
};