#include "Border.h"
#include "Render/Material.h"
#include "Render/Renderer.h"
#include "Render/Shader/ShaderProgram.h"

void Border::OnInit()
{
    Renderer::OnInit();
    StencilFunc.func = GL_NOTEQUAL;
    StencilFunc.ref = 1;
    StencilMask = 0x00;
    // EnableDepthTest = false;
}

void Border::OnUpdate()
{
    Renderer::OnUpdate();
}