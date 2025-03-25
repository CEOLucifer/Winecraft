#pragma once

#include "Std/Basic.h"
#include "Std/SmartPtr.h"

/// 字体网格
class FontMesh
{
private:
    u32 vao = 0;
    u32 vbo = 0;

public:
    FontMesh();

    ~FontMesh();

    void Use();

    u32 GetVbo()
    {
        return vbo;
    }

public:
    static Sp<FontMesh> Create();
};