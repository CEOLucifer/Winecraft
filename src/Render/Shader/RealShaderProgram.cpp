#include "Render/Shader/RealShaderProgram.h"

void RealShaderProgram::onSetTextureLocation()
{
    // 设置uniform纹理位置。这一步和Renderer Draw函数中glActiveTexture对应。
    SetInt("material.diffuse", 0);
    SetInt("material.specular", 1);
}