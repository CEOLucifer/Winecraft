#pragma once


#include "Node/Node.h"
#include "Render/Renderer.h"


class Renderer;

class Cube : public Renderer
{
public:
    void OnInit() override;

    void OnUpdate() override;
};