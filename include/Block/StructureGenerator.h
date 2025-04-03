#pragma once

#include "Std/Math.h"
#include "Std/SmartPtr.h"

class Section;

class Lattice;

/// 处理结构生成
class StructureGenerator
{
public:
    /// 生成树木。在指定位置。
    /// \param bwc
    static void CreateTree(i32vec3 bwc);
};