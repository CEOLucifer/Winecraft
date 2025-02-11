#version 330 core
out vec4 FragColor;

uniform vec4 diffuse; // 在OpenGL程序代码中设定这个变量
uniform vec4 light;

void main()
{
    FragColor = diffuse * light;
}