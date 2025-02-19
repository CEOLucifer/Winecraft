#include "Render/RenderSystem.h"
#include "GLFW/glfw3.h"
#include "Render/Renderer.h"
#include "Debug/Debug.h"
#include <format>
#include <algorithm>

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
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);



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
    // 以下3行似乎也会影响glClear的效果。放这里好点
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 调用每个渲染器的Draw函数
    for (auto renderer : renderVec)
    {
        renderer->Draw(*camera.get());
    }


    glfwSwapBuffers(window);
}

void RenderSystem::SortAll()
{
    ranges::sort(renderVec,
                 [](auto a, auto b) { return a->GetOrder() > b->GetOrder(); });
}