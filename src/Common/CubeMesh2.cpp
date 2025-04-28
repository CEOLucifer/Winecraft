#include <glad/glad.h>
#include "Common/CubeMesh2.hpp"
#include "Std/Basic.h"

CubeMesh2::~CubeMesh2()
{
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
}

void CubeMesh2::OnNewObject()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
}

Vec<float> CubeMesh2::vertices = {-0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f,
                                  0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f,
                                  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
                                  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f};

Vec<u32> CubeMesh2::indices = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6,
                               6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7};

Sp<CubeMesh2> CubeMesh2::instance = nullptr;
