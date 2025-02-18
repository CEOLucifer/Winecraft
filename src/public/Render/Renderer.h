#pragma once

#include "Node/Node3D.h"
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "StencilFunc.h"
#include "StencilOp.h"

class Camera;
class Mesh;
class Material;

/// @brief 渲染器
///
class Renderer : public Node3D
{
public:
    StencilOp StencilOp;
    StencilFunc StencilFunc;
    int StencilMask = 0x00;

private:
    /// @brief 网格
    std::shared_ptr<Mesh> mesh;
    int polygonMode = GL_FILL;
    /// @brief 材质
    std::shared_ptr<Material> material;

public:
    void OnInit() override;

    void Draw(Camera& camera);

    void SetMesh(std::shared_ptr<Mesh> value) { mesh = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetMaterial(std::shared_ptr<Material> value) { material = value; }

    std::shared_ptr<Material> GetMaterial() { return material; }
};