#pragma once


#include "Typedef.h"


class Texture;
class RenderBuffer;

class FrameBuffer
{
private:
    uint32_t id;
    Sp<Texture> texture; 
    Sp<RenderBuffer> renderBuffer;

public:
    void Destroy();

    void BindTexture(Sp<Texture> tex, int attachment);

    void BindTexture(Sp<Texture> tex);

    void BindRGBA(Sp<Texture> tex);

    void BindDepthStencil(Sp<Texture> tex);

    void BindRenderBuffer(Sp<RenderBuffer> renderBuffer);

    bool IsCompleted();

    uint32_t GetID() { return id; }

public:
    static Sp<FrameBuffer> Create();

    static Sp<FrameBuffer> CreateNormal();
};