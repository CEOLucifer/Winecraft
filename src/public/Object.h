#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Transform.h"
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Object : public Transform
{
private:
    std::shared_ptr<Mesh> mesh;
    int polygonMode = GL_FILL;
    std::shared_ptr<ShaderProgram> shaderProgram = 0;
    std::vector<std::shared_ptr<Texture>> texs;

public:
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

public:
    static std::shared_ptr<Object> Create();
};