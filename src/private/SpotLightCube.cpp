#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material.h"

void SpotLightCube::OnInit()
{
    spotLight = Node::Create<SpotLight>();
    spotLight->position = {10, 0, 0};

    renderer = Node::Create<Renderer>();
}

void SpotLightCube::OnUpdate(float deltaTime)
{
    renderer->GetMaterial()->shaderProgram->SetVec3("lightColor",
                                                    spotLight->Color);
}