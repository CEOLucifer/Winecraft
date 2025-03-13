#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 bTexCoords;

uniform mat4 uModel;

void main()
{
    vec2 pos = vec2(uModel * vec4(aPos, 0, 1));

    gl_Position =
    vec4(pos.x, pos.y, -1.0, 1.0);
    bTexCoords = aTexCoords;
}