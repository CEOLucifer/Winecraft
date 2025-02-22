#pragma once

#include "Mesh1.h"
#include "Mesh3.h"

class MeshFactory
{
public:
    Sp<Mesh3> CreateRaw();

    Sp<Mesh3> CreateCube();

    Sp<Mesh3> CreatePlane();

    Sp<Mesh3> CreateSkyBoxCube();

    Sp<Mesh1> CreateMesh1();

    Sp<Mesh1> CreateMesh1_Skybox();
};