#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "Resource/Resource.h"
#include "Render/Shader.h"
#include "Std/SmartPtr.h"
#include "glm/glm.hpp"

class Renderer;
class Camera;

/// @brief shader程序。是shader的链接产品。
///
class ShaderProgram : public Resource
{
private:
    uint32_t id = 0;

public:
    virtual ~ShaderProgram();

    uint32_t GetID() { return id; }

    void OnCreated(const JsonDocument& doc) override;

    void Use();

    // uniform工具函数

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec2(const std::string& name, const glm::vec2& value);
};