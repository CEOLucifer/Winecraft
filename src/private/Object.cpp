#include "Object.h"
#include <cstdint>
#include "ShaderProgram.h"

uint32_t Object::vao_next_id = 1;
uint32_t Object::vbo_next_id = 1;
uint32_t Object::ebo_next_id = 1;

void Object::Draw()
{
    glBindVertexArray(vao);
    glUseProgram(shaderProgram->GetID());

    // 绑定纹理
    for (int i = 0; i < texs.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texs[i]->GetID());
    }

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

std::shared_ptr<Object>
Object::Create(std::vector<float>&& vertices, std::vector<uint32_t>&& indices,
               std::shared_ptr<ShaderProgram> shaderProgram,
               std::vector<std::shared_ptr<Texture>> texs)
{
    std::shared_ptr<Object> obj(new Object);
    obj->vertices = vertices;
    obj->indices = indices;
    obj->texs = texs;

    glGenVertexArrays(vao_next_id, &obj->vao);
    ++vao_next_id;
    glBindVertexArray(obj->vao);

    glGenBuffers(vbo_next_id, &obj->vbo);
    ++vbo_next_id;
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, obj->vertices.size() * sizeof(float),
                 obj->vertices.data(), GL_STATIC_DRAW);

    // 位置属性
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
    //                       (void*)0);
    // glEnableVertexAttribArray(0);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glGenBuffers(ebo_next_id, &obj->ebo);
    ++ebo_next_id;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 obj->indices.size() * sizeof(uint32_t), obj->indices.data(),
                 GL_STATIC_DRAW);



    obj->shaderProgram = shaderProgram;

    return obj;
};