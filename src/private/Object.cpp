#include "Object.h"
#include <cstdint>

uint32_t Object::vao_next_id = 1;
uint32_t Object::vbo_next_id = 1;
uint32_t Object::ebo_next_id = 1;

void Object::Draw()
{
    glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glUseProgram(shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    glDrawElements(GL_TRIANGLES, vertices.size() / 3, GL_UNSIGNED_INT, 0);
}

std::shared_ptr<Object> Object::Create(std::vector<float>&& vertices,
                                       std::vector<uint32_t>&& indices,
                                       uint32_t shaderProgram)
{
    std::shared_ptr<Object> obj(new Object);
    obj->vertices = vertices;
    obj->indices = indices;

    glGenVertexArrays(vao_next_id, &obj->vao);
    ++vao_next_id;
    glBindVertexArray(obj->vao);

    glGenBuffers(vbo_next_id, &obj->vbo);
    ++vbo_next_id;
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, obj->vertices.size() * sizeof(float),
                 obj->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0); // 启用顶点着色器的第0个输入属性


    glGenBuffers(ebo_next_id, &obj->ebo);
    ++ebo_next_id;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 obj->indices.size() * sizeof(uint32_t), obj->indices.data(),
                 GL_STATIC_DRAW);



    obj->shaderProgram = shaderProgram;

    return obj;
};