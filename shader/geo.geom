#version 330 core
layout(points) in;

// 三角形带输出
layout(triangle_strip, max_vertices = 5) out;

void build_house(vec4 position)
{
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:左下
    EmitVertex();
    gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0); // 2:右下
    EmitVertex();
    gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0); // 3:左上
    EmitVertex();
    gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0); // 4:右上
    EmitVertex();
    gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0); // 5:顶部
    EmitVertex();
    EndPrimitive();

    // 绘制的规则是：先根据前3个顶点绘制出一个三角形，之后每个顶点可对应一个三角形
}

void main() { build_house(gl_in[0].gl_Position); }