#pragma once

#include <GL/gl.h>

class StencilOp
{
public:
    GLenum stencilFail = GL_KEEP;
    GLenum depthFail = GL_KEEP;
    GLenum depthPass = GL_KEEP;
};