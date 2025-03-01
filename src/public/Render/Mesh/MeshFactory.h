#pragma once

#include "Mesh1.h"
#include "Mesh2.h"
#include "Mesh3.h"

class MeshFactory
{
public:

    static Sp<Mesh2> CreateMesh2_Control();
};