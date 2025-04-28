#pragma once

#include "Std/Basic.h"
#include "Core/Object.h"
#include "Render/Vertex.h"
#include "Std/Vec.h"

class CubeMesh2 : public Object
{
private:
    u32 vbo;

    u32 ebo;

public:
    ~CubeMesh2() override;

    void OnNewObject() override;

    u32 GetVbo()
    {
        return vbo;
    }

    u32 GetEbo()
    {
        return ebo;
    }

public:
    static Vec<float> vertices;

    static Vec<u32> indices;

    static Sp<CubeMesh2> instance;

public:
    static Sp<CubeMesh2> GetInstance()
    {
        if (!instance)
        {
            instance = Object::NewObject<CubeMesh2>();
        }
        return instance;
    }

    static u32 GetIndicesCnt()
    {
        return indices.size();
    };
};