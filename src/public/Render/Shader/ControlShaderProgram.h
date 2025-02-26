#pragma once

#include "Render/Shader/ShaderProgram.h"

class ControlShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};