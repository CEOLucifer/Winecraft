#pragma once

#include "Mesh.h"
#include "Render/Vertex2.h"
#include <vector>

class Mesh2 : public Mesh
{
public:
    std::vector<Vertex2> vertices;

public:
    void SetVertices(std::vector<Vertex2>&& value);

    const std::vector<Vertex2>& GetVertices() { return vertices; }

    uint32_t GetVerticeCount() override { return vertices.size(); }

private:
    static Sp<Mesh2> control;

public:
    static Sp<Mesh2> LoadControl();
};