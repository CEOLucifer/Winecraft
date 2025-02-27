#pragma once

#include "glm/glm.hpp"
#include "Core/Node.h"
#include "Typedef.h"

class FrameBuffer;

/// @brief 摄像机
class Camera : public Node
{
private:
    float width = 800;
    float height = 600;
    float near = 0.1f;
    float far = 100.0f;
    float fov = 45.0f;

    /// @brief 渲染的目标帧缓冲
    Sp<FrameBuffer> targetFrameBuffer;

    glm::vec3 clearColor = {0.1, 0.1, 0.1};

public:
    float GetWidth() { return width; }
    float GetHeight() { return height; }
    float GetAspect() { return width / height; }
    float GetNear() { return near; }
    float GetFar() { return far; }
    float GetFov() { return fov; }

    void Awake() override;

    void Update() override;

    void OnRender();

    void SetTargetFrameBuffer(Sp<FrameBuffer> value)
    {
        targetFrameBuffer = value;
    }

    glm::mat4 GetProjectionMat();
};