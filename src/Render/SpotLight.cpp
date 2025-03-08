#include "Render/SpotLight.h"
#include "Render/RenderSystem.h"

void SpotLight::Awake()
{
    RenderSystem::Instance()->SetSpotLight(CastTo<SpotLight>());
    Color = {1.0f, 1.0f, 1.0f};
}