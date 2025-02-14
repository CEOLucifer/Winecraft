#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"
#include "ShaderProgram.h"

void SpotLightCube::OnInit()
{
    spotLight = Node::Create<SpotLight>();
    spotLight->position = {10, 0, 0};

    renderer = Node::Create<Renderer>();
}

void SpotLightCube::OnUpdate(float deltaTime)
{
    renderer->GetShaderProgram()->SetVec3("lightColor", spotLight->Color);
}