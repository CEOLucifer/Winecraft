#include "glad/glad.h"
#include "Render/Mesh/Mesh_2D_Point.h"

Sp<Mesh_2D_Point> Mesh_2D_Point::CreateRaw()
{
    Sp<Mesh_2D_Point> This(new Mesh_2D_Point);
    This->GenBuffers();
    return This;
}

void Mesh_2D_Point::SetVertices(std::vector<float>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
                          (void*)(0));
    glEnableVertexAttribArray(0);
}
