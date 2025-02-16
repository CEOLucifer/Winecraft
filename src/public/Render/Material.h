#pragma once

#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include <memory>

class Texture;
class ShaderProgram;

/// @brief 材质
///
class Material : public Resource
{
public:
    std::shared_ptr<Texture> diffuseTex;
    std::shared_ptr<Texture> specularTex;
    /// @brief shader程序
    std::shared_ptr<ShaderProgram> shaderProgram;
    float shininess = 32.0;
};

class MaterialFactory : public ResourceFactory<Material>
{
public:
    static std::shared_ptr<Material> CreateRaw();
};