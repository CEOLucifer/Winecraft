#pragma once

#include "Node/Node3D.h"
#include <memory>

class SpotLight;
class Renderer;

class SpotLightCube : public Node3D
{
public:
    std::shared_ptr<SpotLight> spotLight;
    std::shared_ptr<Renderer> renderer;

public:
    void OnInit() override;
};