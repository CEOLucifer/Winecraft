#include "Resource/ResourceSystem.h"
#include "Render/Shader/ControlShaderProgram.h"
#include "Render/Shader/RealShaderProgram.h"
#include "Render/Shader/SkyboxShaderProgram.h"
#include "Render/Texture.h"

void ResourceSystem::Cache(std::shared_ptr<Resource> res)
{
    resMap.insert({res->GetPath(), res});
}

void ResourceSystem::RegisterAllResources()
{
    // 在这里注册所有Resource子类。
    RegisterResource<Texture>("Texture");

    // ShaderProgram
    RegisterResource<ControlShaderProgram>("ControlShaderProgram");
    RegisterResource<RealShaderProgram>("RealShaderProgram");
    RegisterResource<ShaderProgram>("ShaderProgram");
    RegisterResource<SkyboxShaderProgram>("SkyboxShaderProgram");

    RegisterResource<Shader>("Shader"); 
}

void ResourceSystem::OnLoad() { RegisterAllResources(); }
