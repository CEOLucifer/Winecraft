#pragma once

#include "ShaderProgram.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <glad/glad.h>

class Object
{
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    int polygonMode = GL_FILL;
    std::shared_ptr<ShaderProgram> shaderProgram = 0;

public:
    void Draw();

    void SetShaderProgram(std::shared_ptr<ShaderProgram> value) { shaderProgram = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;

public:
    static std::shared_ptr<Object> Create(std::vector<float>&& vertices,
                                          std::vector<uint32_t>&& indices,
                                          std::shared_ptr<ShaderProgram> shaderProgram);
};