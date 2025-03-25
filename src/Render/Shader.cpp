#include "glad/glad.h"
#include "Render/Shader.h"
#include "Debug/Debug.h"

using namespace std;

Shader::~Shader() { glDeleteShader(id); }

void Shader::OnResourceCreation(const JsonDocument& doc)
{
    string path = doc["path"];

    auto src = FileHelper::ReadFile(path);

    int type;
    string str_type = doc["type"];
    if (str_type == "vert")
    {
        type = GL_VERTEX_SHADER;
    }
    else if (str_type == "frag")
    {
        type = GL_FRAGMENT_SHADER;
    }
    else if (str_type == "geom")
    {
        type = GL_GEOMETRY_SHADER;
    }
    else
    {
        Debug::LogError(format("unknown shader type:{}", str_type));
    }

    id = glCreateShader(type);
    char* _src = src.data();
    glShaderSource(id, 1, &_src, NULL);
    glCompileShader(id);
    // 检查顶点着色器是否编译成功
    {
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            Debug::LogError(
                format("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog));
        }
    }
}