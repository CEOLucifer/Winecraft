#include "ShaderProgram.h"
#include <iostream>

uint32_t ShaderProgram::Create(std::vector<uint32_t> shaders)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    for (auto each : shaders)
    {
        glAttachShader(shaderProgram, each);
    }
    glLinkProgram(shaderProgram);
    // 检查着色器程序是否链接成功
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::shaderProgram::LINK_FAILED\n"
                      << infoLog << std::endl;
        }
    }
    return shaderProgram;
}
