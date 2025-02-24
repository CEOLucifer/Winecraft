#include "Render/DirectionalLight.h"
#include "Render/RenderSystem.h"

void DirectionalLight::Awake()
{
    RenderSystem::Instance()->SetDirectionalLight(CastTo<DirectionalLight>());
}