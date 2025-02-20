#pragma once

#include <glad/glad.h>
#include "BlendFunc.h"
#include "FaceCull.h"
#include "Node/Node3D.h"
#include <memory>
#include <glm/glm.hpp>
#include "StencilFunc.h"
#include "StencilOp.h"
#include "Texture.h"
#include "Typedef.h"

class Camera;
class Mesh;
class Material;

/// @brief 渲染器
///
class Renderer : public Node3D
{
public:
    // 模板测试相关

    StencilOp StencilOp;
    StencilFunc StencilFunc;
    int StencilMask = 0x00;
    bool EnableDepthTest = true;

    // 混合相关

    bool EnableBlend = false;
    BlendFunc BlendFunc;

    FaceCull FaceCull;

private:
    /// @brief 网格
    std::shared_ptr<Mesh> mesh;

    int polygonMode = GL_FILL;

    /// @brief 材质
    std::shared_ptr<Material> material;

    int order = 0;

public:
    void OnInit() override;

    void Draw(Camera& camera);

    void SetMesh(std::shared_ptr<Mesh> value) { mesh = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetMaterial(std::shared_ptr<Material> value) { material = value; }

    std::shared_ptr<Material> GetMaterial() { return material; }

    void SetOrder(int value);

    int GetOrder() { return order; }
};