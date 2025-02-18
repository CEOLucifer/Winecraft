#include "Cube.h"
#include "Render/Renderer.h"

void Cube::OnInit()
{
    Renderer::OnInit();
    StencilFunc.func = GL_ALWAYS;
    StencilFunc.ref = 1;
    StencilMask = 0xFF;
    EnableDepthTest = true;
}

void Cube::OnUpdate(float deltaTime)
{
    // rotation.y += deltaTime * 10;
    // renderer->rotation.x += deltaTime * 10;
}