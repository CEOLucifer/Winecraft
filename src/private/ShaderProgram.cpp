#include "ShaderProgram.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <memory>

using namespace std;

shared_ptr<ShaderProgram>
ShaderProgram::Create(const vector<shared_ptr<Shader>>& shaders)
{
    shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram);
    shaderProgram->id = glCreateProgram();
    for (auto each : shaders)
    {
        glAttachShader(shaderProgram->id, each->GetID());
    }
    glLinkProgram(shaderProgram->id);
    // 检查着色器程序是否链接成功
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram->id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram->id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::shaderProgram::LINK_FAILED\n"
                      << infoLog << std::endl;
        }
    }
    return shaderProgram;
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUseProgram(id);
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUseProgram(id);
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
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
