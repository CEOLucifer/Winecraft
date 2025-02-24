#pragma once


#include "Render/Renderer.h"


class Renderer;

class Cube : public Renderer
{
public:
    void Awake() override;

    void Update() override;
};