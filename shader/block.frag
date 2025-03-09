#version 330 core

in vec3 bTexCoords;

out vec4 FragColor;

uniform samplerCube texCube;

void main() { FragColor = texture(texCube, bTexCoords); }