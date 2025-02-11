#include "Mesh.h"
#include "DrawMode.h"
#include "Vertex.h"
#include <cstddef>
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

    glGenBuffers(ebo_next_id, &This->ebo);
    ++ebo_next_id;

    return This;
}

void Mesh::SetVertices(std::vector<Vertex>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void*)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);
    // 法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, TexCoord)));
    glEnableVertexAttribArray(2);
}

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
