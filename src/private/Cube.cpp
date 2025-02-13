#include "Cube.h"
#include "Render/Renderer.h"

void Cube::OnInit() { renderer = Node::Create<Renderer>(); }

void Cube::OnUpdate(float deltaTime)
{
    renderer->rotation.y += deltaTime * 10;
    // renderer->rotation.x += deltaTime * 10;
}