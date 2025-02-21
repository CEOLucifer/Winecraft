#include "Camera.h"
#include "Render/FrameBuffer.h"
#include "Render/RenderSystem.h"
#include "Render/Renderer.h"

void Camera::OnUpdate() {}

void Camera::OnRender()
{
    // 帧缓冲
    if (targetFrameBuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetFrameBuffer->GetID());
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // 以下3行似乎也会影响glClear的效果。放这里好点
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);

    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClearDepth(1);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    // 调用每个渲染器的Draw函数
    for (auto each : RenderSystem::Instance()->renderVec)
    {
        each->Draw(*this);
    }
}

void Camera::OnInit()
{
    // 注册到渲染系统。
    RenderSystem::Instance()->AddCamera(
        dynamic_pointer_cast<Camera>(weak.lock()));
}
