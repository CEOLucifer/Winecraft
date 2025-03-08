#pragma once


#include "../Typedef.h"


class Texture;
class RenderBuffer;

/// @brief 帧缓冲
class FrameBuffer
{
private:
    uint32_t id;

    /// 纹理。用于存储颜色。帧缓冲至少有一个颜色附件才是完整合法的。
    /// 绘制命令产生的颜色都会存储于这个纹理中。
    Sp<Texture> texture;

    /// 渲染缓冲。一般用于存储模板值和深度值。可以为空。
    Sp<RenderBuffer> renderBuffer;

public:
    ~FrameBuffer();

    void BindTexture(Sp<Texture> tex, int attachment);

    void BindTexture(Sp<Texture> tex);

    void BindRGBA(Sp<Texture> tex);

    void BindDepthStencil(Sp<Texture> tex);

    void BindRenderBuffer(Sp<RenderBuffer> renderBuffer);

    /// @brief 检查附件完整性
    bool IsCompleted();

    uint32_t GetID() { return id; }

    Sp<Texture> GetTexture() { return texture; }

public:
    static Sp<FrameBuffer> Create();

    /// @brief 创建常用帧缓冲。用于直接进行摄像机渲染。
    /// 
    /// @param width 
    /// @param height 
    /// @return Sp<FrameBuffer> 
    static Sp<FrameBuffer> CreateUtility(int width, int height);
};