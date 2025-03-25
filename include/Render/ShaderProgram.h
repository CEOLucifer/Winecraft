#pragma once

#include "Resource/Resource.h"
#include "Std/SmartPtr.h"
#include <glm/glm.hpp>
#include "Std/Basic.h"

class Renderer;
class Camera;

/// @brief shader程序。是shader的链接产品。
///
class ShaderProgram : public Resource
{
private:
    u32 id = 0;

public:
    ~ShaderProgram() override;

    u32 GetID() const { return id; }

    void OnResourceCreation(const JsonDocument& doc) override;

    void Use();

    // uniform工具函数

    void SetBool(const String& name, bool value) const;
    void SetInt(const String& name, int value) const;
    void SetFloat(const String& name, float value) const;
    void SetMat4(const String& name, const glm::mat4& value);
    void SetMat3(const String& name, const glm::mat3& value);
    void SetVec4(const String& name, const glm::vec4& value);
    void SetVec3(const String& name, const glm::vec3& value);
    void SetVec2(const String& name, const glm::vec2& value);
};