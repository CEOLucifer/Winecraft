#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform vec2 viewportSize;
uniform mat3 model;

void main()
{
    vec2 _model = vec2(model * vec3(aPos, 1));

    gl_Position =
        vec4(_model.x / viewportSize.x, _model.y / viewportSize.y, -1.0, 1.0);
    TexCoords = aTexCoords;
}