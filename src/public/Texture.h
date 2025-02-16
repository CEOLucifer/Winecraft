#pragma once

#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include <cstdint>
#include <memory>
#include <glad/glad.h>
#include <string>

/// @brief 纹理
/// 
class Texture : public Resource
{
    friend class TextureFactory;

private:
    /// @brief opengl id 
    /// 
    uint32_t id;

    /// @brief 类型。表明这个纹理是漫反射还是镜面反射等等纹理 
    /// 
    std::string type;

public:
    ~Texture() { glDeleteTextures(1, &id); }

    uint32_t GetID() { return id; }
};

class TextureFactory : public ResourceFactory<Texture>
{
public:
    void onCreate(std::shared_ptr<Texture> res, std::string path) override;
};