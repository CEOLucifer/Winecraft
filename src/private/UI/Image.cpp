#include <glad/glad.h>
#include "UI/Image.h"
#include "Core/Branch.h"
#include "Render/Mesh/MeshFactory.h"
#include "Render/Material/ControlMaterial.h"
#include "Render/Material/Material.h"
#include "Render/Shader/ControlShaderProgram.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Shader/Shader.h"
#include "Render/Renderer.h"
#include "Typedef.h"
#include "Render/Texture.h"


void Image::Awake()
{
    texture = Resource::Load<Texture>("res/texture/awesomeface.json");
}

void Image::OnAdded()
{
    renderer = GetParent().lock()->GetChildOrAdd<Renderer>();

    auto mat = Resource::Load<ControlMaterial>("res/material/control.json");
    renderer->SetMaterial(mat);

    renderer->SetMesh(Mesh2::LoadControl());

    Up<ImageAddition> addition(new ImageAddition);
    addition->image = CastTo<Image>();
    renderer->SetAddition(std::move(addition));
}

void ImageAddition::Add()
{
    glActiveTexture(GL_TEXTURE0);
    if (image && image->texture)
    {
        glBindTexture(GL_TEXTURE_2D, image->texture->GetID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}