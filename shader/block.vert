#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aTexCoords;
layout(location = 3) in mat4 aModel;
layout(location = 7) in uint aTexInd;

out vec3 bTexCoords;
flat out uint bTexInd;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    bTexCoords = aPos;
    gl_Position = vec4(uProj * uView * aModel * vec4(aPos, 1));
    bTexInd = aTexInd;
}