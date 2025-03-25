#include <glad/glad.h>
#include "UI/FontMesh.h"
#include "Render/Vertex2.h"

FontMesh::FontMesh()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 预留6 * sizeof(Vertex2)空间的显存
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2),
                 nullptr, GL_DYNAMIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void*) (offsetof(Vertex2, Position)));
    glEnableVertexAttribArray(0);
    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2),
                          (void*) (offsetof(Vertex2, TexCoord)));
    glEnableVertexAttribArray(1);
}

FontMesh::~FontMesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void FontMesh::Use()
{
    glBindVertexArray(vao);
}

Sp<FontMesh> FontMesh::Create()
{
    Sp<FontMesh> This(new FontMesh);
    return This;
}