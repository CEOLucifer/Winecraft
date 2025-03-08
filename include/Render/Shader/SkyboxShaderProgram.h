#pragma once

#include "ShaderProgram.h"

class SkyboxShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};