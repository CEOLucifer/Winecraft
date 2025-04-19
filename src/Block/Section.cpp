#include <glad/glad.h>
#include "Block/Section.h"
#include "Core/Transform.h"
#include "Block/BlockSystem.h"
#include "Render/Vertex.h"
#include "Block/StructureGenerator.h"
#include "Block/WorldInfo.h"
#include "Common/CubeMesh.h"
#include "Mathf.h"

Section::Section() {}

Section::~Section() { ClearOpenGL(); }

void Section::Set_swc(i32vec2 value)
{
    if (isCached)
    {
        BlockSystem::Instance()->RemoveSectionCache(swc);
    }
    swc = value;
    BlockSystem::Instance()->CacheSection(CastTo<Section>());
    isCached = true;
}


void Section::InitOpenGL()
{
    if (isOpenGLInited)
    {
        return;
    }

    u32 size = Section::Size * Section::Size * Section::Height;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);


    // 方块顶点vbo
    glBindBuffer(GL_ARRAY_BUFFER, CubeMesh::GetInstance()->GetVbo());
    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, Position)));
    // 法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, Normal)));
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, TexCoord)));
    // todo : !!!纹理属性其实没必要，以后删

    // ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeMesh::GetInstance()->GetEbo());
    // 只要以上这一行，就能将ebo绑定到vao了。



    // 创建其它vbo

    // aModels
    aModels.reserve(size);
    glGenBuffers(1, &aModelsVbo);
    // aModel 属性，实例化数组
    glBindBuffer(GL_ARRAY_BUFFER, aModelsVbo);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4), nullptr,
                 GL_DYNAMIC_DRAW);
    GLsizei vec4Size = sizeof(glm::vec4);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void*)(1 * vec4Size));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void*)(2 * vec4Size));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void*)(3 * vec4Size));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);




    // aTexInds
    aTexInds.reserve(size);
    glGenBuffers(1, &aTexIndsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, aTexIndsVbo);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(u32), nullptr, GL_DYNAMIC_DRAW);
    // aTexInds 属性，实例化数组
    glVertexAttribIPointer(7, 1, GL_UNSIGNED_INT, sizeof(u32), (void*)(0));
    glVertexAttribDivisor(7, 1);
    // !!!设置glsl整数类型要用glVertexAttribIPointer，而不是glVertexAttribPointer。







    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    isOpenGLInited = true;
}

void Section::ClearOpenGL()
{
    if (!isOpenGLInited)
    {
        return;
    }

    glDeleteBuffers(1, &aModelsVbo);
    glDeleteBuffers(1, &aTexIndsVbo);
    glDeleteVertexArrays(1, &vao);

    isOpenGLInited = false;
}

void Section::FillWith(Block block)
{
    for (int x = 0; x < Size; ++x)
    {
        for (int y = 0; y < Height; ++y)
        {
            for (int z = 0; z < Size; ++z)
            {
                Blocks[x][y][z] = block;
            }
        }
    }
}

void Section::GenerateCave()
{
    for (i32 x = 0; x < Size; ++x)
    {
        for (i32 y = 1; y < Height; ++y)
        {
            for (i32 z = 0; z < Size; ++z)
            {
                i32vec3 bwc = {swc.x * Size + x, y, swc.y * Size + z};
                f32 v = Mathf::Noise3D(1, 16, 0, bwc);
                if (v < 0.2)
                {
                    // 挖空
                    Blocks[x][y][z] = 0;
                }
            }
        }
    }
}

void Section::GenerateTree()
{
    for (i32 x = 0; x < Size; ++x)
    {
        for (i32 z = 0; z < Size; ++z)
        {
            i32vec2 bwc = {swc.x * Size + x, swc.y * Size + z};
            i32 height = WorldInfo::GetHeight(bwc);
            // 下方一格没有方块，continue
            auto lowerBlock =
                BlockSystem::Instance()->GetBlock({bwc.x, height - 1, bwc.y});
            if (!lowerBlock || (*lowerBlock).id == 0)
            {
                continue;
            }

            // 根据温度，生成植物结构
            f32 temperature = WorldInfo::GetTemperature(bwc);

            if (0.3 <= temperature && temperature < 0.7)
            {
                // 树
                f32 treeRate = WorldInfo::GetTreeRate(bwc);
                if (treeRate < 0.005)
                {
                    StructureGenerator::CreateTree({bwc.x, height, bwc.y});
                }
            }
            else if (temperature >= 0.7)
            {
                // 仙人掌
                f32 rate = WorldInfo::GetCactusRate(bwc);
                if (rate < 0.002)
                {
                    StructureGenerator::CreateCactus({bwc.x, height, bwc.y});
                }
            }
        }
    }
}

void Section::GenerateBase()
{
    // 这个函数处理区块的随机生成

    u32 xx = swc.x;
    u32 zz = swc.y;
    for (i32 x = 0; x < Section::Size; ++x)
    {
        for (i32 z = 0; z < Section::Size; ++z)
        {
            glm::i32vec2 bwc = {xx * Section::Size + x, zz * Section::Size + z};

            // 高度
            u32 height = WorldInfo::GetHeight(bwc);

            for (u32 y = 0; y < height && y < Section::Height; ++y)
            {
                if (y == height - 1)
                {
                    // 表层

                    // 生态系统。目前只影响表层
                    // 温度
                    f32 temperature = WorldInfo::GetTemperature(bwc);
                    if (temperature < 0.3)
                    {
                        // 雪地
                        Blocks[x][y][z] = 2;
                    }
                    else if (0.3 <= temperature && temperature < 0.7)
                    {
                        // 草原
                        Blocks[x][y][z] = 1;
                    }
                    else
                    {
                        // 沙漠
                        Blocks[x][y][z] = 5;
                    }
                }
                else if (height - y > 5)
                {
                    // 泥层
                    Blocks[x][y][z] = 3;
                }
                else
                {
                    // 岩层
                    Blocks[x][y][z] = 4;
                }
            }
        }
    }
}

void Section::GenerateFull()
{
    GenerateBase();
    GenerateCave();
    GenerateTree();
    isFull = true;
}

void Section::FreshBufferData()
{
    aModels.clear();
    aTexInds.clear();

    // 把每个方块的model传入
    for (i32 x = 0; x < Section::Size; ++x)
    {
        for (i32 y = 0; y < Section::Height; ++y)
        {
            for (i32 z = 0; z < Section::Size; ++z)
            {
                //                i32 ind = x * Section::Height * Section::Size
                //                + y * Section::Size + z;

                glm::mat4 model;

                // 判断方块是否应该被渲染
                u32 isRender = 1;
                // 没有方块，continue
                if (Blocks[x][y][z] == 0)
                {
                    isRender = 0;
                }
                else
                {
                    // 上下左右前后都有方块，continue
                    int bwcX = swc.x * Section::Size;
                    int bwcY = swc.y * Section::Size;
                    auto up = BlockSystem::Instance()->GetBlock(
                        {bwcX + x, y + 1, bwcY + z});
                    auto down = BlockSystem::Instance()->GetBlock(
                        {bwcX + x, y - 1, bwcY + z});
                    auto left = BlockSystem::Instance()->GetBlock(
                        {bwcX + x - 1, y, bwcY + z});
                    auto right = BlockSystem::Instance()->GetBlock(
                        {bwcX + x + 1, y, bwcY + z});
                    auto forward = BlockSystem::Instance()->GetBlock(
                        {bwcX + x, y, bwcY + z + 1});
                    auto back = BlockSystem::Instance()->GetBlock(
                        {bwcX + x, y, bwcY + z - 1});

                    if (up && (*up).id != 0 && down && (*down).id != 0 &&
                        left && (*left).id != 0 && right && (*right).id != 0 &&
                        forward && (*forward).id != 0 && back &&
                        (*back).id != 0)
                    {
                        isRender = 0;
                    }
                }

                if (isRender == 1)
                {
                    // 添加一个此方块的aModel
                    Transform t;
                    t.Position =
                        glm::vec3(
                            swc.x * Section::GetSize(), 0,
                            swc.y * Section::GetSize())  // 区块的区块世界的坐标
                        + glm::vec3(x * 1, y * 1, z * 1) // 方块相对区块坐标
                        + glm::vec3(0.5, 0.5, 0.5);
                    model = t.GetModelMat();
                    //                    aModels[ind] = model;
                    aModels.push_back(model);

                    // ！！！巨坑：如上:
                    //
                    //          glm::vec3(swc.x * (int)Section::GetSize(), 0,
                    //          swc.y * (int)Section::GetSize())
                    //
                    // int和u32类型相乘，必须把u32强转为int，否则默认是int强转u32。如果int是负数，则会将其变成很大的u32！还是不要用u32了！

                    //                    aTexInds[ind] = Blocks[x][y][z];
                    aTexInds.push_back(Blocks[x][y][z]);
                }
            }
        }
    }

    glBindVertexArray(vao);

    // aModels
    glBindBuffer(GL_ARRAY_BUFFER, aModelsVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, aModels.size() * sizeof(glm::mat4),
                    aModels.data());

    // aTexInds
    glBindBuffer(GL_ARRAY_BUFFER, aTexIndsVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, aTexInds.size() * sizeof(u32),
                    aTexInds.data());


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    isFreshBufferData = true;
}
