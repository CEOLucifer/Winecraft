#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SingleColorMaterial.h"
#include "Render/SpotLight.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material.h"
#include <memory>

using namespace std;

void SpotLightCube::OnInit()
{
    spotLight = Node::Create<SpotLight>();
    spotLight->position = {10, 0, 0};

    renderer = Node::Create<Renderer>();
    renderer->position = {10, 0, 0};
}

void SpotLightCube::OnUpdate(float deltaTime) {}