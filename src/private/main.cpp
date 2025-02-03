#include "Object.h"
#include "Shader.h"
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"

using namespace std;

void onFrameBufferResize(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char* fragmentShaderSource_2 =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1f, 0.0f, 1.0f);\n"
    "}\0";

void Run()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);

    // 事件监听
    glfwSetFramebufferSizeCallback(window, onFrameBufferResize);

    // 创建顶点着色器
    unsigned int vertexShader =
        Shader::Create(GL_VERTEX_SHADER, vertexShaderSource);
    // 创建片段着色器
    unsigned int fragmentShader =
        Shader::Create(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // 创建着色器程序
    unsigned int shaderProgram =
        ShaderProgram::Create({vertexShader, fragmentShader});


    // 创建片段着色器
    unsigned int fragmentShader_2 =
        Shader::Create(GL_FRAGMENT_SHADER, fragmentShaderSource_2);
    unsigned int shaderProgram_2 =
        ShaderProgram::Create({vertexShader, fragmentShader_2});


    // 删除着色器
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);



    auto obj1 = Object::Create(
        {
            0, 0, 0,        // 右上角
            -0.5f, 0, 0.0f, // 右下角
            0, 0.5f, 0.0f,  //

        },
        {
            0, 1, 2, //
        },
        shaderProgram);

    auto obj2 = Object::Create(
        {
            0, 0, 0,       // 右上角
            0.5f, 0, 0.0f, // 右下角
            0, 0.5f, 0.0f, //

        },
        {
            0, 1, 2, //
        },
        shaderProgram_2);


    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        // 检查并调用事件
        glfwPollEvents();
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ...
        obj1->Draw();
        obj2->Draw();


        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

int main()
{
    try
    {
        Run();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
    return 0;
}