#pragma once

#include "ShaderProgram.h"
#include <cstdint>
#include <memory>

class Texture
{
private:
    uint32_t id;
    

public:
    ~Texture() { glDeleteTextures(1, &id); }

    uint32_t GetID() { return id; }

public:
    static std::shared_ptr<Texture> Create(std::string path, int mode);
};