#include "glad/glad.h"
#include "Block/BlockRenderPass.h"
#include "Core/Transform.h"
#include "Render/ShaderProgram.h"
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"
#include "Render/Vertex.h"
#include "Block/BlockSystem.h"

using namespace std;


void BlockRenderPass::OnNewObject()
{
    RenderPass::OnNewObject();

    instance = CastTo<BlockRenderPass>();

    FaceCull.Enable = true;
    FaceCull.CullFace = GL_BACK;
    FaceCull.FrontFace = GL_CCW;

    EnableBlend = true;

//    polygonMode = GL_LINE;

    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/block.json");
    for (i32 i = 0; i < 10; ++i)
    {
        shaderProgram->SetInt(std::format("uTexCubes[{}]", i), i);
    }
}

void BlockRenderPass::RenderCustom(Sp<Camera> camera)
{
    shaderProgram->Use();
    shaderProgram->SetMat4("uView", camera->GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("uProj", camera->GetProjectionMat());

    // 方块纹理
    auto texGrassBlock = Resource::Load<Texture>("res/texture/grass_block.json");
    texGrassBlock->Use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);

    auto texSnowBlock = Resource::Load<Texture>("res/texture/snow_block.json");
    texSnowBlock->Use(GL_TEXTURE1, GL_TEXTURE_CUBE_MAP);

    auto texStone = Resource::Load<Texture>("res/texture/stone.json");
    texStone->Use(GL_TEXTURE2, GL_TEXTURE_CUBE_MAP);

    auto texDirt = Resource::Load<Texture>("res/texture/dirt.json");
    texDirt->Use(GL_TEXTURE3, GL_TEXTURE_CUBE_MAP);

    auto texSand = Resource::Load<Texture>("res/texture/sand.json");
    texSand->Use(GL_TEXTURE4, GL_TEXTURE_CUBE_MAP);

    auto texOakLog = Resource::Load<Texture>("res/texture/oak_log.json");
    texOakLog->Use(GL_TEXTURE5, GL_TEXTURE_CUBE_MAP);

    auto texOakLeaves = Resource::Load<Texture>("res/texture/oak_leaves.json");
    texOakLeaves->Use(GL_TEXTURE6, GL_TEXTURE_CUBE_MAP);

    auto texCactus = Resource::Load<Texture>("res/texture/cactus.json");
    texCactus->Use(GL_TEXTURE7, GL_TEXTURE_CUBE_MAP);

    Lattice& lattice = BlockSystem::Instance()->GetLattice();
    // 渲染每个区块
    for (u32 xx = 1; xx < lattice.GetFullSize() - 1; ++xx)
    {
        for (u32 zz = 1; zz < lattice.GetFullSize() - 1; ++zz)
        {
            Sp<Section> section = lattice.GetSections()[xx][zz];
            u32 indiceCnt = Section::GetIndices().size();
            u32 instanceCnt = section->GetaModels().size();
            glBindVertexArray(section->GetVao());
            glDrawElementsInstanced(GL_TRIANGLES, indiceCnt, GL_UNSIGNED_INT, nullptr, instanceCnt);
        }
    }
    glBindVertexArray(0);
}


Sp<BlockRenderPass> BlockRenderPass::instance = nullptr;
