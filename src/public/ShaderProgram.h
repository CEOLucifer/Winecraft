#pragma once

#include <cstdint>
#include <vector>
#include <glad/glad.h>
class ShaderProgram
{
public:
    static uint32_t Create(std::vector<uint32_t> shaders);
};