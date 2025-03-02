#include "Resource/ResourceSystem.h"
#include "Render/Material/ControlMaterial.h"
#include "Render/Material/InstanceMaterial.h"
#include "Render/Material/RealMaterial.h"
#include "Render/Material/SingleColorMaterial.h"
#include "Render/Material/SkyboxMaterial.h"
#include "Render/Shader/ControlShaderProgram.h"
#include "Render/Shader/RealShaderProgram.h"
#include "Render/Shader/Shader.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Shader/SkyboxShaderProgram.h"
#include "Resource/Creator.h"
#include "Render/Texture.h"
#include "Resource/Resource.h"

void ResourceSystem::Cache(std::shared_ptr<Resource> res)
{
    resMap.insert({res->GetPath(), res});
}

void ResourceSystem::RegisterAllResources()
{
    // 在这里注册所有Resource子类。
    RegisterResource<Texture>("Texture");

    // 材质
    RegisterResource<ControlMaterial>("ControlMaterial");
    RegisterResource<Material>("Material");
    RegisterResource<RealMaterial>("RealMaterial");
    RegisterResource<SingleColorMaterial>("SingleColorMaterial");
    RegisterResource<SkyboxMaterial>("SkyboxMaterial");
    RegisterResource<InstanceMaterial>("InstanceMaterial");
    
    // ShaderProgram
    RegisterResource<ControlShaderProgram>("ControlShaderProgram");
    RegisterResource<RealShaderProgram>("RealShaderProgram");
    RegisterResource<ShaderProgram>("ShaderProgram");
    RegisterResource<SkyboxShaderProgram>("SkyboxShaderProgram");

    RegisterResource<Shader>("Shader"); 
}

void ResourceSystem::OnLoad() { RegisterAllResources(); }
