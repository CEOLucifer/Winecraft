#include "Render/Camera.h"
#include "glad/glad.h"
#include "Render/FrameBuffer.h"
#include "Render/RenderSystem.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Render/RenderPass.h"

void Camera::Update()
{}

void Camera::Render()
{
    // // 帧缓冲
    // if (targetFrameBuffer)
    // {
    //     glBindFramebuffer(GL_FRAMEBUFFER, targetFrameBuffer->GetID());
    // }
    // else
    // {
    //     glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // }

    // // 以下4行似乎也会影响glClear的效果。放这里好点
    // glStencilMask(0xFF);
    // glStencilFunc(GL_ALWAYS, 0, 0xFF);
    // glEnable(GL_DEPTH_TEST);
    // glDepthMask(GL_TRUE);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    // glClearDepth(1);
    // glClearStencil(0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT);

    // 调用每个渲染通道的Pass函数
    for (auto each: RenderSystem::Instance()->renderPassVec)
    {
        each->Render(CastTo<Camera>());
    }
}

void Camera::Awake()
{
    // 注册到渲染系统。
    RenderSystem::Instance()->AddCamera(CastTo<Camera>());
}

glm::mat4 Camera::GetProjectionMat()
{
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), GetAspect(), near, far);
    return projection;
}
