#pragma once

#include <glad/glad.h>
#include "Node/Node3D.h"
#include <glm/glm.hpp>
#include "Typedef.h"

class Camera;
class Mesh;
class Material;

/// @brief 渲染器
///
class Renderer : public Node3D
{
private:
    /// @brief 网格
    Sp<Mesh> mesh;

    int polygonMode = GL_FILL;

    /// @brief 材质
    Sp<Material> material;

    int order = 0;

public:
    void OnInit() override;

    void Draw(Camera& camera);

    void SetMesh(Sp<Mesh> value) { mesh = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetMaterial(Sp<Material> value) { material = value; }

    Sp<Material> GetMaterial() { return material; }

    void SetOrder(int value);

    int GetOrder() { return order; }

    
};