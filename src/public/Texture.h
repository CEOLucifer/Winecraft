#pragma once

#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include <array>
#include <cstdint>
#include "Typedef.h"
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

    /// @brief 类型。表明这个纹理是漫反射还是镜面反射等等纹理。暂时无用。
    ///
    std::string type;

    int internalFormt;

    int format;

public:
    ~Texture();

    uint32_t GetID() { return id; }

    int GetInternalFormat() { return internalFormt; }
};

class TextureFactory : public ResourceFactory<Texture>
{
public:
    void onCreate(Sp<Texture> res, std::string path) override;

    /// @brief 创建一个空白的纹理
    ///
    /// @param format GL_RGB, GL_RGBA等等
    /// @param width
    /// @param height
    /// @return Sp<Texture>
    Sp<Texture> CreateRaw(int internalFormat, int format, int width, int height,
                          int type);

    Sp<Texture> CreateRGBA(int width, int height);

    Sp<Texture> CreateDepthStencil(int width, int height);

    Sp<Texture> CreateCube(const std::array<std::string, 6>& paths);
};