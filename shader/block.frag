#version 330 core

in vec3 bTexCoords;
flat in uint bTexInd;
flat in vec4 bData;

out vec4 FragColor;

uniform samplerCube uTexCubes[10];

void main()
{
    vec4 texColor = texture(uTexCubes[bTexInd - 1u], bTexCoords);

    if (texColor.a < 0.05)
    {
        discard;
    }

    FragColor = texColor;

    // 树叶
    if (bTexInd == 7u)
    {
        FragColor *= vec4(0.47, 0.67, 0.18, 1);
    }
}