#pragma once

#include <glm/glm.hpp>
#include <cstdint>
#include <memory>
#include <vector>
#include <glad/glad.h>
#include "Shader.h"
#include <iostream>

class Renderer;
class Camera;

/// @brief shader程序。是shader的链接产品。
///
class ShaderProgram
{
private:
    uint32_t id;

public:
    virtual ~ShaderProgram() { glDeleteProgram(id); }

    uint32_t GetID() { return id; }

    // uniform工具函数

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetVec3(const std::string& name, const glm::vec3& value);

    /// @brief 由子类重写。
    ///
    /// @param renderer
    /// @param camera
    virtual void OnUpdateUniform(std::shared_ptr<Renderer> renderer,
                                 Camera& camera)
    {}

private:
    void init(const std::vector<std::shared_ptr<Shader>>& shaders);

public:
    template <typename T>
    static std::shared_ptr<T>
    Create(const std::vector<std::shared_ptr<Shader>>& shaders)
    {
        std::shared_ptr<T> shaderProgram(new T);
        shaderProgram->init(shaders);
        return shaderProgram;
    }
};