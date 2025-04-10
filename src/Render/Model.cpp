//#include "Render/Model.h"
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include <iostream>
//#include <memory>
//#include "Render/Vertex.h"
//#include "Render/Mesh/Mesh3.h"
//
//using namespace std;
//
//
//void Model::loadModel(std::string path)
//{
////    Assimp::Importer import;
////    const aiScene* scene =
////        import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
////
////    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
////        !scene->mRootNode)
////    {
////        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
////        return;
////    }
////    directory = path.substr(0, path.find_last_of('/'));
////
////    processNode(scene->mRootNode, scene);
//}
//
//void Model::processNode(aiNode* node, const aiScene* scene)
//{
////    // 处理节点所有的网格（如果有的话）
////    for (unsigned int i = 0; i < node->mNumMeshes; i++)
////    {
////        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
////        meshes.push_back(processMesh(mesh, scene));
////    }
////    // 接下来对它的子节点重复这一过程
////    for (unsigned int i = 0; i < node->mNumChildren; i++)
////    {
////        processNode(node->mChildren[i], scene);
////    }
//}
//
//shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
//{
////    vector<Vertex> vertices;
////    vector<unsigned int> indices;
////    vector<shared_ptr<Texture>> textures;
////
////    vertices.reserve(mesh->mNumVertices);
////    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
////    {
////        Vertex vertex;
////        // 处理顶点位置、法线和纹理坐标
////        glm::vec3 vector;
////        vector.x = mesh->mVertices[i].x;
////        vector.y = mesh->mVertices[i].y;
////        vector.z = mesh->mVertices[i].z;
////        vertex.Position = vector;
////
////        vector.x = mesh->mNormals[i].x;
////        vector.y = mesh->mNormals[i].y;
////        vector.z = mesh->mNormals[i].z;
////        vertex.Normal = vector;
////
////        if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
////        {
////            glm::vec2 vec;
////            vec.x = mesh->mTextureCoords[0][i].x;
////            vec.y = mesh->mTextureCoords[0][i].y;
////            vertex.TexCoord = vec;
////        }
////        else
////        {
////            vertex.TexCoord = glm::vec2(0.0f, 0.0f);
////        }
////
////        vertices.push_back(vertex);
////    }
////
////    // 处理索引
////    int cnt = 0;
////    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
////    {
////        aiFace face = mesh->mFaces[i];
////        cnt += face.mNumIndices;
////    }
////    indices.reserve(cnt);
////
////    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
////    {
////        aiFace face = mesh->mFaces[i];
////        for (uint32_t j = 0; j < face.mNumIndices; j++)
////            indices.push_back(face.mIndices[j]);
////    }
////
////    // 处理材质
////    if (mesh->mMaterialIndex >= 0)
////    {
////        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
////        vector<shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(
////            material, aiTextureType_DIFFUSE, "texture_diffuse");
////        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
////
////        vector<shared_ptr<Texture>> specularMaps = loadMaterialTextures(
////            material, aiTextureType_SPECULAR, "texture_specular");
////        textures.insert(textures.end(), specularMaps.begin(),
////                        specularMaps.end());
////    }
////
////    auto myMesh = Mesh3::CreateRaw();
////    myMesh->SetVertices(std::move(vertices));
////    myMesh->SetIndices(std::move(indices));
////    myMesh->SetDefaultTexs(std::move(textures));
////
////    return myMesh;
//}
//
//vector<shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat,
//                                                        aiTextureType type,
//                                                        string typeName)
//{
////    vector<shared_ptr<Texture>> textures;
////    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
////    {
////        aiString str;
////        mat->GetTexture(type, i, &str);
////        shared_ptr<Texture> texture =
////            Resource::Load<Texture>(directory + "/" + str.C_Str());
////        // texture.id = TextureFromFile(str.C_Str(), directory);
////        // texture.type = typeName;
////        // texture.path = str;
////        textures.push_back(texture);
////    }
////    return textures;
//}