#include <glad/glad.h>
#include "UI/MeshControl.h"
#include <vector>
#include "Render/Vertex2.h"

using namespace std;

MeshControl::MeshControl()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vector<Vertex2> vertices = {
            {{-0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f,  -0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f},  {1.0f, 1.0f}},
            {{-0.5f, 0.5f},  {0.0f, 1.0f}},
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void*) (offsetof(Vertex2, Position)));
    glEnableVertexAttribArray(0);
    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void*) (offsetof(Vertex2, TexCoord)));
    glEnableVertexAttribArray(1);


    indices = {0, 1, 2, 2, 3, 0};
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

}

MeshControl::~MeshControl()
{
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void MeshControl::Use()
{
    glBindVertexArray(vao);
}