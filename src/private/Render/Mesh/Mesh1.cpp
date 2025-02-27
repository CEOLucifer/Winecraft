#include "glad/glad.h"
#include "Render/Mesh/Mesh1.h"

void Mesh1::SetVertices(std::vector<Vertex1>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex1),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1),
                          (void*)(offsetof(Vertex1, Position)));
    glEnableVertexAttribArray(0);
}