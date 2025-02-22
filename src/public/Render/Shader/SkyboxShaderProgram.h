#pragma once

#include "Render/Shader/ShaderProgram.h"

class SkyboxShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};