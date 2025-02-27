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
    TextureFactory texFac;
    texture = texFac.Create("res/awesomeface.png");
}

void Image::OnAdded()
{
    renderer = GetParent().lock()->GetChildOrAdd<Renderer>();

    auto vert = Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/control.vert");
    auto frag =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/control.frag");

    auto sp = ShaderProgram::Create<ControlShaderProgram>({vert, frag});


    MaterialFactory matFac;
    auto mat = matFac.CreateRaw<ControlMaterial>();
    mat->shaderProgram = sp;

    renderer->SetMaterial(mat);


    MeshFactory meshFac;
    auto mesh = meshFac.CreateMesh2_Control();

    renderer->SetMesh(mesh);


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