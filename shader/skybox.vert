#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 bTexCor;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    bTexCor = aPos;
    gl_Position = uProj * uView * vec4(aPos, 1.0);
}