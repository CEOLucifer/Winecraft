#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal; // 暂无用
layout (location = 2) in vec2 iTexCoords;
layout (location = 3) in mat4 iModel; // 实例化数组

out vec2 oTexCoords;

uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    oTexCoords = iTexCoords;
    gl_Position = uProjection * uView * iModel * vec4(iPos, 1.0);
}