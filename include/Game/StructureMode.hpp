#pragma once

#include "Block/Structure.hpp"
#include "Std/Math.h"
#include "Std/String.h"

/// @brief 结构模式
class StructureMode
{
private:
    i32vec3 cor0;
    i32vec3 cor1;

public:
    void Enter();

    void CreateStructure();

    void SaveStructure();

    void Exit();
};