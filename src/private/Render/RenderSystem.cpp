#include "Render/RenderSystem.h"
#include "GLFW/glfw3.h"
#include "Render/Renderer.h"
#include "Debug/Debug.h"
#include "Render/Shader/ShaderProgram.h"
#include <format>

using namespace std;

void RenderSystem::OnLoad()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        Debug::LogError("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Debug::LogError("Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, 800, 600);


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
    Debug::Log(
        format("Maximum nr of vertex attributes supported: {}", nrAttributes));
}

void RenderSystem::OnUnload() { glfwTerminate(); }

void RenderSystem::Render()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearStencil(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 调用每个渲染器的Draw函数
    for (auto renderer : renderVec)
    {
        renderer->Draw(*camera.get());
    }

    glfwSwapBuffers(window);
}
