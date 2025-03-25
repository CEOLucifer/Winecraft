#include "Resource/ResourceSystem.h"
#include "Render/Texture.h"
#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Font/Font.h"

void ResourceSystem::Cache(std::shared_ptr<Resource> res)
{
    resMap.insert({res->GetPath(), res});
}

void ResourceSystem::RegisterAllResources()
{
    // 在这里注册所有Resource子类。
    RegisterResource<Texture>("Texture");

    // ShaderProgram
    RegisterResource<ShaderProgram>("ShaderProgram");
    RegisterResource<Shader>("Shader");

    RegisterResource<Font>("Font");
}

void ResourceSystem::OnLoad() { RegisterAllResources(); }
