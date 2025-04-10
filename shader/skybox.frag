#version 330 core
in vec3 bTexCor;

out vec4 cFragColor;

uniform samplerCube uTex;

void main()
{    
    cFragColor = texture(uTex, bTexCor);
}