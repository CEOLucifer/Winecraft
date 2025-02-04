#pragma once

#include <cstdint>
#include <vector>
#include <glad/glad.h>

class Shader;

class ShaderProgram
{
private:
    uint32_t id;

public:
    uint32_t GetID() { return id; }

public:
    static std::shared_ptr<ShaderProgram> Create(std::vector<std::shared_ptr<Shader>> shaders);
};