#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 bNormal;
out vec2 bTexCoords;
out vec3 bFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    bFragPos = vec3(model * vec4(aPos, 1.0));
    bNormal = mat3(transpose(inverse(model))) * aNormal;
    // bNormal = aNormal;
    bTexCoords = aTexCoord;
    
    gl_Position = projection * view * vec4(bFragPos, 1.0);
}