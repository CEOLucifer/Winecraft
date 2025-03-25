#pragma once

#include "Std/Basic.h"
#include "Std/Vec.h"
#include "Std/SmartPtr.h"

class ControlMesh
{
private:
    u32 vao = 0;
    u32 vbo = 0;
    u32 ebo = 0;

    Vec<u32> indices;

public:
    ControlMesh();

    ~ControlMesh();

    void Use();

    u32 GetIndiceCount()
    {
       return indices.size();
    }

public:
    static Sp<ControlMesh> Create();
};