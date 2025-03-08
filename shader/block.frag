#version 330 core

in vec3 iTexCoords;

uniform samplerCube tex0;

void main() {
    gl_FragColor = texture(tex0, iTexCoords);
}