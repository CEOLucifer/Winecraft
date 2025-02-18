#pragma once


#include <GL/gl.h>

class StencilFunc
{
public:
    int func = GL_ALWAYS;
    int ref = 1;
    int mask = 0xFF;
};