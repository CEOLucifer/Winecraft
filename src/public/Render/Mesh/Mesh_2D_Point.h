#pragma once

#include "Render/Mesh/Mesh.h"
#include <vector>

class Mesh_2D_Point : public Mesh
{
private:
    std::vector<float> vertices;

public:
    void SetVertices(std::vector<float>&& value);

    uint32_t GetVerticeCount() override { return vertices.size() / 2; }

public:
    static Sp<Mesh_2D_Point> CreateRaw();
};