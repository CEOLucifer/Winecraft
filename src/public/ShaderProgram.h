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

    // uniform工具函数
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

  public:
    static std::shared_ptr<ShaderProgram>
    Create(std::vector<std::shared_ptr<Shader>> shaders);
};