#include "Common/Skybox.h"
#include "Render/Texture.h"
#include "Common/SkyboxRenderPass.h"

void Skybox::Awake()
{
    skyboxCubeMap = Resource::Load<Texture>("res/texture/skybox.json");
    SkyboxRenderPass::Instance()->SetSkybox(CastTo<Skybox>());
}