#include "ShaderProgram.h"
#include "Shader.h"
#include <iostream>
#include <memory>

using namespace std;

shared_ptr<ShaderProgram> ShaderProgram::Create(vector<shared_ptr<Shader>> shaders)
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
