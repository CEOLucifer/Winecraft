#pragma once

#include "Camera.h"
#include "DrawMode.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Transform.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Object : public Transform
{
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    int polygonMode = GL_FILL;
    std::shared_ptr<ShaderProgram> shaderProgram = 0;
    std::vector<std::shared_ptr<Texture>> texs;
    DrawMode drawMode = Indices;




public:
    void Draw(Camera& camera);

    void SetShaderProgram(std::shared_ptr<ShaderProgram> value)
    {
        shaderProgram = value;
    }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetVertices(std::vector<float>&& value);

    void SetIndices(std::vector<uint32_t>&& value);

    void SetTexs(std::vector<std::shared_ptr<Texture>>&& value)
    {
        texs = std::move(value);
    }

private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;

public:
    static std::shared_ptr<Object> Create();
};