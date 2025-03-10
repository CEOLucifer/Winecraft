#pragma once


#include "Core/Node.h"
class Camera;

class CameraController : public Node{
public:
    Sp<Camera> camera;
    float cameraSpeed = 5;
    float cursorSpeed = 0.2;

public:
    void Update() override;
};