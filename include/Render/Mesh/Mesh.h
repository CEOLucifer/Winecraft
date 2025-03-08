#pragma once

#include <cstdint>
#include <vector>
#include "../DrawMode.h"
#include "../../Typedef.h"

class Texture;

/// @brief 网格
class Mesh
{
protected:
    /// @brief 顶点索引
    std::vector<uint32_t> indices;

    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;

    DrawMode drawMode = Normal;

    /// @brief 默认的纹理
    std::vector<Sp<Texture>> defaultTexs;

public:
    void SetIndices(std::vector<uint32_t>&& value);

    const std::vector<uint32_t>& GetIndices() { return indices; }

    uint32_t GetVao() { return vao; };

    DrawMode GetDrawMode() { return drawMode; }

    void SetDefaultTexs(std::vector<Sp<Texture>>&& value)
    {
        defaultTexs = std::move(value);
    }

    virtual uint32_t GetVerticeCount() = 0;

protected:
    void GenBuffers();
};