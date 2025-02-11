#pragma once

#include "DrawMode.h"
#include "Vertex.h"
#include <cstdint>
#include <vector>

/// @brief 网格
class Mesh
{
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    DrawMode drawMode = Normal;

public:
    void SetVertices(std::vector<Vertex>&& value);
    void SetIndices(std::vector<uint32_t>&& value);
    const std::vector<Vertex>& GetVertices() { return vertices; }
    const std::vector<uint32_t>& GetIndices() { return indices; }
    uint32_t GetVao() { return vao; };
    DrawMode GetDrawMode() { return drawMode; }

private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;

public:
    static std::shared_ptr<Mesh> Create();

    static std::shared_ptr<Mesh> CreateCube();

    static std::shared_ptr<Mesh> CreatePlane();
};