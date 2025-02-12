#pragma once


#include "Node/Node.h"
#include "Render/Renderer.h"


class Cube : public Node
{
public:
    std::shared_ptr<Renderer> renderer;

public:
    void Init() override { renderer = Renderer::Create(); }

    void Update(float deltaTime) override
    {
        renderer->rotation.y += deltaTime * 10;
        // renderer->rotation.x += deltaTime * 10;
    }
};