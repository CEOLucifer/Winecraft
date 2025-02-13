#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"

void SpotLightCube::OnInit()
{
    spotLight = Node::Create<SpotLight>();
    renderer = Node::Create<Renderer>();
}