#include "ShaderProgram.h"

/// @brief 通用着色器程序
class RealShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};