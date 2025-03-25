#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCor;

out vec2 bTexCor;

uniform mat4 uModel;
uniform mat4 uProj;

void main()
{
    vec2 pos = vec2(uProj * uModel * vec4(aPos, 0, 1));
    gl_Position = vec4(pos.xy, -1.0, 1.0);
    bTexCor = aTexCor;
}