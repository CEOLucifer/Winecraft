#include "glad/glad.h"
#include "Render/Mesh/Mesh.h"

void Mesh::SetIndices(std::vector<uint32_t>&& value)
{
    indices = std::move(value);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

    drawMode = Indices;
}

void Mesh::GenBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}
