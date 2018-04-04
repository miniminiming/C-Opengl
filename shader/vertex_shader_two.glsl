#version 330 core

layout (location = 0) in vec3 aPos;//位置变量的属性位置值为0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor; //向片段着色器输出一个颜色
out vec2 TexCoord; //向片段着色器输出一个纹理坐标
void main() {
    gl_Position = vec4(aPos,1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
