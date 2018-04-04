#version 330 core

layout (location = 0) in vec3 aPos;//位置变量的属性位置值为0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;


out vec2 TexCoord; //向片段着色器输出一个纹理坐标
out vec3 ourColor; //向片段着色器输出一个颜色

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform mat4 transform;
void main() {
//    gl_Position = transform * vec4(aPos, 1.0f);//矩阵进行位置变换
    gl_Position = projection*view*model*vec4(aPos,1.0);

    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);//将纹理上下倒置了一下
//    TexCoord = aTexCoord;//原本是正的

//        gl_Position = vec4(aPos,1.0);
        ourColor = aColor;
//        TexCoord = aTexCoord;
}
