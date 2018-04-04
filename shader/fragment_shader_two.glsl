#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main() {
    //ourTexture是纹理采样器
//    FragColor = texture(ourTexture,TexCoord) * vec4(ourColor,1.0);
//    FragColor = texture(ourTexture,TexCoord) ;
//    FragColor = texture(texture2,TexCoord) ;
    //混合两个纹理，第三个参数是指第二个纹理占所有纹理的比例
    FragColor = mix(texture(texture1,TexCoord)* vec4(ourColor,1.0),
                        texture(texture2,TexCoord)* vec4(ourColor,1.0),0.3) ;
}
