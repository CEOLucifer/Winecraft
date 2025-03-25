#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCor;

out vec2 bTexCor;

uniform mat4 uProj;

void main()
{
    gl_Position = uProj * vec4(aPos.xy, -1.0, 1.0);
    bTexCor = aTexCor;
}