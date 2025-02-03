#pragma once

#include <cstddef>
#include <cstdint>
#include <glad/glad.h>

class Shader
{
private:
    uint32_t id;

public:
  static uint32_t Create(int type, const char *src);
};