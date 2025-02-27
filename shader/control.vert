#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform vec2 viewportSize;

void main()
{
    gl_Position =
        vec4(aPos.x / viewportSize.x, aPos.y / viewportSize.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}