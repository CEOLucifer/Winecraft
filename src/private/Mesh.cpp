#include "Mesh.h"
#include "DrawMode.h"
#include <memory>
#include <glad/glad.h>

using namespace std;

uint32_t Mesh::vao_next_id = 1;
uint32_t Mesh::vbo_next_id = 1;
uint32_t Mesh::ebo_next_id = 1;

shared_ptr<Mesh> Mesh::Create()
{
    shared_ptr<Mesh> This(new Mesh);

    glGenVertexArrays(vao_next_id, &This->vao);
    ++vao_next_id;
    glBindVertexArray(This->vao);

    glGenBuffers(vbo_next_id, &This->vbo);
    ++vbo_next_id;

    return This;
}

void Mesh::SetVertices(std::vector<float>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh::SetIndices(std::vector<uint32_t>&& value)
{
    indices = std::move(value);
    glBindVertexArray(vao);
    glGenBuffers(ebo_next_id, &ebo);
    ++ebo_next_id;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

    drawMode = Indices;
}
