#include "ShaderProgram.h"

/// @brief 通用着色器程序
class UniversalShaderProgram : public ShaderProgram
{
public:
    void OnUpdateUniform(std::shared_ptr<Renderer> renderer, Camera& camera) override;
};