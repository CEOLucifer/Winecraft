#include "Render/Shader/ShaderProgram.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <glad/glad.h>
#include "Debug/Debug.h"

using namespace std;

void ShaderProgram::SetFloat(const std::string& name, float value) const
{
    glUseProgram(id);
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::SetInt(const std::string& name, int value) const
{
    glUseProgram(id);
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::SetBool(const std::string& name, bool value) const
{
    glUseProgram(id);
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUseProgram(id);
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value)
{
    glUseProgram(id);
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUseProgram(id);
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void ShaderProgram::init(const std::vector<std::shared_ptr<Shader>>& shaders)
{
    id = glCreateProgram();
    for (auto each : shaders)
    {
        glAttachShader(id, each->GetID());
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
            Debug::LogError(format("ERROR::SHADER::shaderProgram::LINK_FAILED\n{}", infoLog));
        }
    }
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }
