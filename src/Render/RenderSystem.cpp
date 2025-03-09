#include "glad/glad.h"
#include "Render/RenderSystem.h"
#include "GLFW/glfw3.h"
#include "Debug/Debug.h"
#include <format>
#include <algorithm>
#include "Render/Camera.h"

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
    // 调用每个摄像机的Render
    for (auto each : cameraVec)
    {
        each->Render();
    }

    glfwSwapBuffers(window);
}

void RenderSystem::onFrameBufferResize(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
}

glm::vec2 RenderSystem::GetWindowSize()
{
    int w;
    int h;
    glfwGetWindowSize(window, &w, &h);
    return {w, h};
}
