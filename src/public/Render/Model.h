#pragma once

#include "Render/Mesh/Mesh.h"
#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include "Texture.h"
#include <memory>
#include <vector>
#include <assimp/scene.h>

class aiNode;
class aiScene;
class aiMesh;
class aiMaterial;

/// @brief 模型。是例如.obj模型资源的表示。
/// 
class Model : public Resource
{
    friend class ModelFactory;

private:
    std::vector<std::shared_ptr<Mesh>> meshes;

    /// @brief 模型所在目录。用于查找.obj同级的纹理。 
    /// 
    std::string directory;

public:
    const std::vector<std::shared_ptr<Mesh>>& GetMeshes() { return meshes; }

private:
    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene);

    std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<std::shared_ptr<Texture>>
    loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                         std::string typeName);
};

class ModelFactory : public ResourceFactory<Model>
{
protected:
    void onCreate(std::shared_ptr<Model> res, std::string path) override;
};