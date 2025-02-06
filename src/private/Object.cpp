#include "Object.h"
#include <cstdint>
#include "DrawMode.h"
#include "ShaderProgram.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

uint32_t Object::vao_next_id = 1;
uint32_t Object::vbo_next_id = 1;
uint32_t Object::ebo_next_id = 1;

void Object::Draw(Camera& camera)
{
    glBindVertexArray(vao);
    glUseProgram(shaderProgram->GetID());

    // 绑定纹理。
    for (int i = 0; i < texs.size(); ++i)
    {
        // opengl状态里至少有16个纹理。通过下面api设置纹理。
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texs[i]->GetID());
    }

    // 变换
    // 世界矩阵
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);

    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotate = rotateZ * rotateY * rotateX;
    model = rotate * model;

    model = glm::translate(model, position);

    // 观察矩阵
    glm::mat4 view = glm::mat4(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, -camera.position);

    // 投影矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(camera.GetFov()), camera.GetAspect(),
                         camera.GetNear(), camera.GetFar());

    shaderProgram->SetMat4("model", model);
    shaderProgram->SetMat4("view", view);
    shaderProgram->SetMat4("projection", projection);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    if (drawMode == Normal)
    {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    else if (drawMode == Indices)
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
}

std::shared_ptr<Object> Object::Create()
{
    std::shared_ptr<Object> obj(new Object);

    glGenVertexArrays(vao_next_id, &obj->vao);
    ++vao_next_id;
    glBindVertexArray(obj->vao);

    glGenBuffers(vbo_next_id, &obj->vbo);
    ++vbo_next_id;

    glGenBuffers(ebo_next_id, &obj->ebo);
    ++ebo_next_id;

    return obj;
};

void Object::SetVertices(std::vector<float>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

void Object::SetIndices(std::vector<uint32_t>&& value)
{
    indices = std::move(value);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);
}
