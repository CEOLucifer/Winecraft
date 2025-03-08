#pragma once

#include "ShaderProgram.h"

class ControlShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};