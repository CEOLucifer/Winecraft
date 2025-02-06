#pragma once

#include "DrawMode.h"
#include <cstdint>
#include <vector>

class Mesh
{
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    DrawMode drawMode = Normal;

public:
    void SetVertices(std::vector<float>&& value);
    void SetIndices(std::vector<uint32_t>&& value);
    std::vector<float>& GetVertices() { return vertices; }
    std::vector<uint32_t>& GetIndices() { return indices; }
    uint32_t GetVao() { return vao; };
    DrawMode GetDrawMode() { return drawMode; }

private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;

public:
    static std::shared_ptr<Mesh> Create();
};