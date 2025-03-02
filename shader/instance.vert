#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 models[100];
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(models[gl_InstanceID] * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(models[gl_InstanceID]))) * aNormal;
    // Normal = aNormal;
    TexCoords = aTexCoord;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}