#version 330 core
in vec2 bTexCor;

out vec4 cColor;

uniform sampler2D uTex;
uniform vec4 uColor;

void main()
{
    vec4 sampled = texture(uTex, bTexCor);
    cColor = uColor * sampled;
}