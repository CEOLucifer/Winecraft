#pragma once

#include "DrawMode.h"
#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include "Texture.h"
#include "Vertex.h"
#include <cstdint>
#include <vector>

/// @brief 网格
class Mesh : Resource
{
    friend class MeshFactory;

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    DrawMode drawMode = Normal;
    std::vector<std::shared_ptr<Texture>> defaultTexs;

public:
    void SetVertices(std::vector<Vertex>&& value);
    void SetIndices(std::vector<uint32_t>&& value);
    const std::vector<Vertex>& GetVertices() { return vertices; }
    const std::vector<uint32_t>& GetIndices() { return indices; }
    uint32_t GetVao() { return vao; };
    DrawMode GetDrawMode() { return drawMode; }
    void SetDefaultTexs(std::vector<std::shared_ptr<Texture>>&& value)
    {
        defaultTexs = std::move(value);
    }
};

class MeshFactory : public ResourceFactory<Mesh>
{
private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;


public:
    std::shared_ptr<Mesh> CreateRaw();

    std::shared_ptr<Mesh> CreateCube();

    std::shared_ptr<Mesh> CreatePlane();

protected:
    void onCreate(std::shared_ptr<Mesh> res, std::string path) override;
};