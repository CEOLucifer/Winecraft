#pragma once


#include "Render/Renderer.h"
#include "Update/Updatable.h"


class Cube : public Updatable
{
public:
    std::shared_ptr<Renderer> renderer;

public:
    void Init() { renderer = Renderer::Create(); }

    void Update(float deltaTime) override
    {
        renderer->rotation.y += deltaTime * 10;
        renderer->rotation.x += deltaTime * 10;
    }
};