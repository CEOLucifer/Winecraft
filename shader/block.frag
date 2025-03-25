#version 330 core

in vec3 bTexCoords;
flat in uint bTexInd;

out vec4 FragColor;

uniform samplerCube uTexCubes[10];

void main()
{
    FragColor = texture(uTexCubes[bTexInd - 1u], bTexCoords);
}