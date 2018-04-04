#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 ourColor;


uniform sampler2D texture1;
uniform sampler2D texture2;
void main() {
    //混合两个纹理，第三个参数是指第二个纹理占所有纹理的比例
    FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.3) ;
// FragColor = mix(texture(texture1,TexCoord)* vec4(ourColor,1.0),
//                        texture(texture2,TexCoord)* vec4(ourColor,1.0),0.3) ;
}
