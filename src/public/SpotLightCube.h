#pragma once

#include "Core/Component.h"
#include "Typedef.h"

class SpotLight;
class Renderer;

class SpotLightCube : public Component
{
public:
    Sp<SpotLight> spotLight;
    Sp<Renderer> renderer;

public:
    void Awake() override;

    void Update() override;
};