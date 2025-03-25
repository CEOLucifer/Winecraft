#version 330 core
in vec2 bTexCor;

out vec4 cColor;

uniform sampler2D uTex;
uniform vec4 uColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTex, bTexCor).r);
    cColor = uColor * sampled;
}

