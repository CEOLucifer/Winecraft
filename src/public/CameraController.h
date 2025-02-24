#pragma once

#include "Core/Component.h"
#include <memory>

class Camera;

class CameraController : public Component
{
public:
    std::shared_ptr<Camera> camera;
    float cameraSpeed = 3;
    float cursorSpeed = 0.2;


public:
    void Update() override;
};