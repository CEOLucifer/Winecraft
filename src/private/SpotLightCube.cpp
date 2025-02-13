#include "SpotLightCube.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"

void SpotLightCube::Init()
{
    spotLight = Node::Create<SpotLight>();
    renderer = Node::Create<Renderer>();
}