#pragma once

#include "Block/Block.h"
#include "Std/Math.h"
#include "Std/Opt.h"

class StaredBlockInfo
{
public:
    Opt<Block> block;
    i32vec3 bwc;
};