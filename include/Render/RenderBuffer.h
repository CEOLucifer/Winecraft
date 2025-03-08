#pragma once

#include <cstdint>
#include "../Typedef.h"

/// @brief 渲染缓冲。
///
class RenderBuffer
{
    // 和纹理Texture类似，但是渲染缓冲是只写不读的，有优化，速度更快。
    // !!!目前只有模板和深度缓冲类型。

private:
    // opengl内部唯一标识符
    uint32_t id;

public:
    ~RenderBuffer();

    uint32_t GetID() { return id; }

public:
    static Sp<RenderBuffer> Create(int width, int height);
};