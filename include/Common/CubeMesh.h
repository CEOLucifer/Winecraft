#pragma once

#include "Std/Basic.h"
#include "Core/Object.h"
#include "Render/Vertex.h"
#include "Std/Vec.h"

class CubeMesh : public Object
{
private:
    u32 vbo;

    u32 ebo;

public:
    ~CubeMesh() override;

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
    static Vec<Vertex> vertices;

    static Vec<u32> indices;

    static Sp<CubeMesh> instance;

public:
    static Sp<CubeMesh> GetInstance()
    {
        if (!instance)
        {
            instance = Object::NewObject<CubeMesh>();
        }
        return instance;
    }

    static u32 GetIndicesCnt()
    {
        return indices.size();
    };
};