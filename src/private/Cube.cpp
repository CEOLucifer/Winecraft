#include "Cube.h"
#include "Render/Renderer.h"

void Cube::Init() { renderer = Node::Create<Renderer>(); }

void Cube::Update(float deltaTime)
{
    renderer->rotation.y += deltaTime * 10;
    // renderer->rotation.x += deltaTime * 10;
}