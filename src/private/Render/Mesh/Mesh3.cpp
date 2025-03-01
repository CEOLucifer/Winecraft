#include "Render/Mesh/Mesh3.h"
#include "Render/DrawMode.h"
#include "Render/Vertex.h"
#include <cstddef>
#include <memory>
#include "glad/glad.h"

using namespace std;


void Mesh3::SetVertices(std::vector<Vertex>&& value)
{
    vertices = std::move(value);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);
    // 法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(offsetof(Vertex, TexCoord)));
    glEnableVertexAttribArray(2);
}



Sp<Mesh3> Mesh3::cube = nullptr;
Sp<Mesh3> Mesh3::plane = nullptr;

Sp<Mesh3> Mesh3::CreateRaw()
{
    Sp<Mesh3> This(new Mesh3);
    This->GenBuffers();
    return This;
}

Sp<Mesh3> Mesh3::LoadCube()
{
    if (cube)
    {
        return cube;
    }

    Sp<Mesh3> This(new Mesh3);
    This->GenBuffers();

    vector<Vertex> vertices = {
        // 前面
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        // 后面
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        // 顶面
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        // 底面
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        // 右面
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        // 左面
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}};

    vector<uint32_t> indices = {// 前面
                                0, 1, 2, 2, 3, 0,
                                // 后面
                                4, 5, 6, 6, 7, 4,
                                // 顶面
                                8, 9, 10, 10, 11, 8,
                                // 底面
                                12, 13, 14, 14, 15, 12,
                                // 右面
                                16, 17, 18, 18, 19, 16,
                                // 左面
                                20, 21, 22, 22, 23, 20};
    This->SetVertices(std::move(vertices));
    This->SetIndices(std::move(indices));

    cube = This;
    return This;
}

Sp<Mesh3> Mesh3::LoadPlane()
{
    if (plane)
    {
        return plane;
    }

    Sp<Mesh3> This(new Mesh3);
    This->GenBuffers();
    vector<Vertex> vertices = {
        //     ---- 位置 ----       ---- 法线 ----     - 纹理坐标 -
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   // 右上
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // 右下
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // 左上
    };

    vector<uint32_t> indices = {
        0, 1, 3, //
        1, 2, 3, //
    };
    This->SetVertices(std::move(vertices));
    This->SetIndices(std::move(indices));

    plane = This;
    return This;
}