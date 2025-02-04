#include "Shader.h"
#include "FileHelper.h"
#include <iostream>

using namespace std;

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
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
    }
    return shader;
}

shared_ptr<Shader> Shader::CreateFromFile(int type, string path)
{
    auto src = FileHelper::ReadFile(path);
    return Create(type, src.data());
}
