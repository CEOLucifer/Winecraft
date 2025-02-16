#include "Render/DirectionalLight.h"
#include "Render/RenderSystem.h"

void DirectionalLight::OnInit()
{
    RenderSystem::Instance()->SetDirectionalLight(CastTo<DirectionalLight>());
}