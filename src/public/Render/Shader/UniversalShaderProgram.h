#include "ShaderProgram.h"

/// @brief 通用着色器程序
class UniversalShaderProgram : public ShaderProgram
{
protected:
    void onSetTextureLocation() override;
};