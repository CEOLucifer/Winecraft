#pragma once

#include "Node/Node.h"
#include <memory>

class Camera;

class CameraController : public Node
{
public:
    std::shared_ptr<Camera> camera;
    float cameraSpeed = 3;
    float cursorSpeed = 50;


public:
    void OnUpdate(float deltaTime) override;
};