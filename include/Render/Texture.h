#pragma once

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

    /// @brief 类型。表明这个纹理是漫反射还是镜面反射等等纹理。暂时无用。
    ///
    String type;

    int internalFormat;

    int format;

public:
    ~Texture() override;

    u32 GetID() const { return id; }

    int GetInternalFormat() const { return internalFormat; }

    void Use(int position, int type);

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
    static Sp<Texture> CreateRaw(int internalFormat, int format, int width,
                                 int height, int type);

    static Sp<Texture> CreateRGBA(int width, int height);

    static Sp<Texture> CreateDepthStencil(int width, int height);
};