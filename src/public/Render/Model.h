#pragma once

#include "Mesh.h"
#include "Texture.h"
#include <memory>
#include <vector>
#include <assimp/scene.h>

class aiNode;
class aiScene;
class aiMesh;
class aiMaterial;

class Model
{
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::string directory;



private:
    /*  函数   */
    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene);

    std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<std::shared_ptr<Texture>>
    loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                         std::string typeName);

public:
    static std::shared_ptr<Model> Create(std::string path);
};