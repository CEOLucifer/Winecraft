#include "Render/SpotLight.h"
#include "Render/RenderSystem.h"

void SpotLight::Init()
{
    RenderSystem::Instance()->SetSpotLight(CastTo<SpotLight>());
}