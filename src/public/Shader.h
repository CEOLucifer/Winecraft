#pragma once

#include <cstddef>
#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <string>

class Shader
{
private:
    uint32_t id;

public:
    ~Shader() { glDeleteShader(id); }

    uint32_t GetID() { return id; }

public:
    static std::shared_ptr<Shader> Create(int type, std::string src);

    static std::shared_ptr<Shader> CreateFromFile(int type, std::string path);
};