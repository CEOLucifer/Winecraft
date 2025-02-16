#pragma once

#include "Mesh.h"
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

class Model : public Resource
{
    friend class ModelFactory;

private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::string directory;

public:
    const std::vector<std::shared_ptr<Mesh>>& GetMeshes() { return meshes; }

private:
    /*  函数   */
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