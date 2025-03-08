#pragma once

#include <GL/gl.h>

class BlendFunc
{
public:
    int SourceFactor = GL_SRC_ALPHA;
    int DestinationFactor = GL_ONE_MINUS_SRC_ALPHA;
};