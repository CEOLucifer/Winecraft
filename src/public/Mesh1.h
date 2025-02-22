#pragma once

#include "Mesh.h"
#include "Vertex1.h"

/// @brief 仅坐标网格
/// 
class Mesh1 : public Mesh
{
private:
    std::vector<Vertex1> vertices;

public:
    void SetVertices(std::vector<Vertex1>&& value);

    std::vector<Vertex1> GetVertices() { return vertices; }

    uint32_t GetVerticeCount() override { return vertices.size(); }
};