#pragma once

#include <GL/gl.h>

class FaceCull
{
public:
    bool Enable = false;
    int CullFace = GL_BACK;
    int FrontFace = GL_CCW;
};