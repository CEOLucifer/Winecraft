#pragma once

#include "Node/Node3D.h"
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera;
class Mesh;
class ShaderProgram;
class Texture;

/// @brief 渲染器
///
class Renderer : public Node3D
{
private:
    /// @brief 网格
    std::shared_ptr<Mesh> mesh;
    int polygonMode = GL_FILL;
    /// @brief shader程序
    std::shared_ptr<ShaderProgram> shaderProgram = 0;
    /// @brief 纹理
    std::vector<std::shared_ptr<Texture>> texs;

public:
    void Init() override;

    void Draw(Camera& camera);

    void SetMesh(std::shared_ptr<Mesh> value) { mesh = value; }

    void SetShaderProgram(std::shared_ptr<ShaderProgram> value)
    {
        shaderProgram = value;
    }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetTexs(std::vector<std::shared_ptr<Texture>>&& value)
    {
        texs = std::move(value);
    }
};