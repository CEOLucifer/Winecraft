#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <glad/glad.h>

class Object
{
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
    int polygonMode = GL_FILL;
    int shaderProgram;

public:
    void Draw();

    void SetShaderProgram(int value) { shaderProgram = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

private:
    static uint32_t vao_next_id;
    static uint32_t vbo_next_id;
    static uint32_t ebo_next_id;

public:
    static std::shared_ptr<Object> Create(std::vector<float>&& vertices,
                                          std::vector<uint32_t>&& indices,
                                          uint32_t shaderProgram);
};