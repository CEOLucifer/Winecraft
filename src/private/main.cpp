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

    // 查询顶点着色器的顶点属性上限
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // 创建顶点着色器
    auto vertexShader =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert1.vert");
    // 创建片段着色器
    auto fragmentShader =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag1.frag");

    // 创建着色器程序
    auto shaderProgram = ShaderProgram::Create({vertexShader, fragmentShader});

    // 删除着色器
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);



    auto obj1 = Object::Create(
        {
            // 位置                         
            0.5f, -0.5f, 0.0f, 
            -0.5f, -0.5f, 0.0f, 
            0.0f, 0.5f, 0.0f, 
        },
        {
            0, 1, 2, //
        },
        shaderProgram);

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
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation =
        //     glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        obj1->Draw();

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