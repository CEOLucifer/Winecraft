#pragma once

#include "Render/RenderSystem.h"
#include <glm/glm.hpp>
#include <memory>
#include "Node/Node3D.h"

/// @brief 摄像机
class Camera : public Node3D
{
private:
    float width = 800;
    float height = 600;
    float near = 0.1f;
    float far = 100.0f;
    float fov = 45.0f;

public:
    float GetWidth() { return width; }
    float GetHeight() { return height; }
    float GetAspect() { return width / height; }
    float GetNear() { return near; }
    float GetFar() { return far; }
    float GetFov() { return fov; }

    void OnInit() override
    {
        RenderSystem::Instance()->camera =
            std::dynamic_pointer_cast<Camera>(weak.lock());
    }
};