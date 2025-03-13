#pragma once

#include <cstdint>
#include <vector>

class MeshControl
{
public:
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;

    std::vector<uint32_t> indices;

public:
    MeshControl();

    ~MeshControl();

    void Use();
};