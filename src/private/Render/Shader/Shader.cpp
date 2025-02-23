#include "Shader.h"
#include "Debug/Debug.h"
#include "FileHelper.h"
#include <iostream>
#include <glad/glad.h>

using namespace std;

Shader::~Shader() { glDeleteShader(id); }

shared_ptr<Shader> Shader::Create(int type, string src)
{
    shared_ptr<Shader> shader(new Shader());
    shader->id = glCreateShader(type);
    char* _src = src.data();
    glShaderSource(shader->id, 1, &_src, NULL);
    glCompileShader(shader->id);
    // 检查顶点着色器是否编译成功
    {
        int success;
        char infoLog[512];
        glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader->id, 512, NULL, infoLog);
            Debug::LogError(format("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog));
        }
    }
    return shader;
}

shared_ptr<Shader> Shader::CreateFromFile(int type, string path)
{
    auto src = FileHelper::ReadFile(path);
    return Create(type, src.data());
}
