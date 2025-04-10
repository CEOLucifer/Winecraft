#pragma once

#include <glad/glad.h>
#include "Resource/Resource.h"
#include "Std/Basic.h"
#include "Std/SmartPtr.h"
#include "Std/String.h"

/// @brief 纹理
///
class Texture : public Resource
{
private:
    /// @brief opengl id
    ///
    u32 id;

    /// GL_TEXTURE_2D、GL_TEXTURE_CUBE_MAP
    GLenum target;

    GLenum internalFormat;

    GLenum format;

public:
    ~Texture() override;

    u32 GetID() const { return id; }

    int GetInternalFormat() const { return internalFormat; }

    void Use(u32 position);

public:
    void OnResourceCreation(const JsonDocument& doc) override;


public:
    // 以下函数主要用于自定义帧缓冲



    /// @brief 创建一个空白的纹理
    ///
    /// @param format GL_RGB, GL_RGBA等等
    /// @param width
    /// @param height
    /// @return Sp<Texture>
    static Sp<Texture> CreateRaw(GLenum internalFormat, GLenum format, int width,
                                 int height, int type);

    static Sp<Texture> CreateRGBA(int width, int height);

    static Sp<Texture> CreateDepthStencil(int width, int height);
};