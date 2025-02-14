#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"

void SpotLightCube::OnInit()
{
    spotLight = Node::Create<SpotLight>();
    spotLight->position = {10, 0, 0};

    renderer = Node::Create<Renderer>();
}