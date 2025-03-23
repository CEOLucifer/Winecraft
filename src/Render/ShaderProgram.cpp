#include "glad/glad.h"
#include "Render/ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"
#include "Render/Shader.h"

using namespace std;

void ShaderProgram::SetFloat(const String& name, float value) const
{
    glUseProgram(id);
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::SetInt(const String& name, int value) const
{
    glUseProgram(id);
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::SetBool(const String& name, bool value) const
{
    glUseProgram(id);
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void ShaderProgram::SetMat4(const String& name, const glm::mat4& value)
{
    glUseProgram(id);
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void ShaderProgram::SetMat3(const String& name, const glm::mat3& value)
{
    glUseProgram(id);
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void ShaderProgram::SetVec4(const String& name, const glm::vec4& value)
{
    glUseProgram(id);
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void ShaderProgram::SetVec3(const String& name, const glm::vec3& value)
{
    glUseProgram(id);
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void ShaderProgram::SetVec2(const String& name, const glm::vec2& value)
{
    glUseProgram(id);
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{ glDeleteProgram(id); }


void ShaderProgram::OnCreated(const JsonDocument& doc)
{
    auto vertShader = Resource::Load<Shader>(doc["vert"]);
    auto fragShader = Resource::Load<Shader>(doc["frag"]);

    id = glCreateProgram();
    glAttachShader(id, vertShader->GetID());
    glAttachShader(id, fragShader->GetID());

    Sp<Shader> geomShader;

    // 可选的几何着色器
    auto geom = doc["geom"];
    if (!geom.isNull())
    {
        auto geomShader = Resource::Load<Shader>(geom);
        glAttachShader(id, geomShader->GetID());
    }

    glLinkProgram(id);
    // 检查着色器程序是否链接成功
    {
        int success;
        char infoLog[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            Debug::LogError(format(
                    "ERROR::SHADER::shaderProgram::LINK_FAILED\n{}", infoLog));
        }
    }

    // 设置uniform采样器索引
    auto samplers = doc["samplers"];
    if (!samplers.isNull())
    {
        JsonArrayConst ar = samplers;
        for (int i = 0; i < ar.size(); ++i)
        {
            SetInt(ar[i].as<string>(), i);
        }
    }
}

void ShaderProgram::Use()
{
    glUseProgram(id);
}
