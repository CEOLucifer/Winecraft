#pragma once

#include "../Vertex.h"
#include <vector>
#include "Mesh.h"

/// @brief 网格。顶点拥有法线、纹理坐标。
class Mesh3 : public Mesh
{
private:
    /// @brief 顶点
    ///
    std::vector<Vertex> vertices;

public:
    void SetVertices(std::vector<Vertex>&& value);

    const std::vector<Vertex>& GetVertices() { return vertices; }

    uint32_t GetVerticeCount() override { return vertices.size(); }


private:
    static Sp<Mesh3> cube;
    static Sp<Mesh3> plane;
    static Sp<Mesh3> skyboxCube;


public:
    static Sp<Mesh3> CreateRaw();
    static Sp<Mesh3> LoadCube();
    static Sp<Mesh3> LoadPlane();
};