#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aTexCoords;

out vec3 bTexCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    bTexCoords = aPos;
    gl_Position = vec4(uProjection * uView * uModel * vec4(aPos, 1));
}