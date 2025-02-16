#include "Render/RenderSystem.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Render/Renderer.h"

void RenderSystem::OnLoad()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);
    // 启用深度检测。此时交换链有深度字段。
    glEnable(GL_DEPTH_TEST);

    // 事件监听
    glfwSetFramebufferSizeCallback(
        window,
        [](auto window, int w, int h)
        {
            auto renderSystem = (RenderSystem*)glfwGetWindowUserPointer(window);
            renderSystem->onFrameBufferResize(window, w, h);
        });

    // 查询顶点着色器的顶点属性上限
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;
}

void RenderSystem::OnUnload() { glfwTerminate(); }

void RenderSystem::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 调用每个渲染器的Draw函数
    for (auto renderer : renderVec)
    {
        renderer->Draw(*camera.get());
    }
}
