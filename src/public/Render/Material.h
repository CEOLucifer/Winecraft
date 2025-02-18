#pragma once

#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include <memory>

class Texture;
class ShaderProgram;
class Camera;

/// @brief 材质
///
class Material : public Resource
{
public:
    /// @brief shader程序
    std::shared_ptr<ShaderProgram> shaderProgram;

public:
    virtual void OnUpdateShaderProgram(Camera& camera) {}
};

class MaterialFactory : public ResourceFactory<Material>
{
public:
    template <typename T> static std::shared_ptr<T> CreateRaw()
    {
        std::shared_ptr<T> This(new T);
        return This;
    }
};