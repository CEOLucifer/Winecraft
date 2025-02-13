#pragma once


#include "Node/Node.h"


class Renderer;

class Cube : public Node
{
public:
    std::shared_ptr<Renderer> renderer;

public:
    void OnInit() override;

    void OnUpdate(float deltaTime) override;
};