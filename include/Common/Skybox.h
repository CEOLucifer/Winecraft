#pragma once

#include "../Core/Node.h"

class Renderer;

class Skybox : public Node
{
private:
    Sp<Renderer> renderer;

public:
    void OnAdded() override;
};