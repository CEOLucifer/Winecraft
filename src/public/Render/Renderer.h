#pragma once

#include <glad/glad.h>
#include "Core/Node.h"
#include <glm/glm.hpp>
#include "Typedef.h"
#include "Addition.h"

class Camera;
class Mesh;
class Material;

/// @brief 渲染器。一次绘制的基本单位。
///
class Renderer : public Node
{
private:
    /// @brief 网格
    Sp<Mesh> mesh;

    int polygonMode = GL_FILL;

    /// @brief 材质
    Sp<Material> material;

    int order = 0;

    Up<Addition> addition;

    int primitiveMode = GL_TRIANGLES;



public:
    void Awake() override;

    void OnDestroyed() override;

    void Draw(Camera& camera);

    void SetMesh(Sp<Mesh> value) { mesh = value; }

    void SetPolygonMode(int value) { polygonMode = value; }

    void SetMaterial(Sp<Material> value) { material = value; }

    Sp<Material> GetMaterial() { return material; }

    void SetOrder(int value);

    int GetOrder() { return order; }

    void SetAddition(Up<Addition> value);

    void SetPrimitiveMode(int value) { primitiveMode = value; }
};