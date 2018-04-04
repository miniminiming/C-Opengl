#version 330 core
#define NR_POINT_LIGHTS 4
out vec4 FragColor;

uniform vec3 viewPos;

//上面用两个纹理，下面用一个接收？并不是，这个是纹理的坐标
//而纹理的对象，是设置给了Light结构体里的diffuse和specular
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    //环境光颜色几乎在所有情况下都等于漫反射颜色，所以不需要环境光，只用漫反射即可
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;//放射光的贴图
    float shininess;//反光度
};

//定向光源
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


//点光源，除了三个光类型，还多了衰减
struct PointLight {
    vec3 position;//光源位置,一般只有点光源用

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    //加个点光源的颜色？
};


//聚光灯
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//变量定义必须在结构体之后
uniform DirLight dirLight;
//NR_POINT_LIGHTS相当于一个常量而已。然后我们依据这个常量创建了一个含有4个点光源的数组
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

//计算定向光，这个相当于C++中的方法定义或是.h文件中的定义
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal,vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



void main() {
        //属性
        vec3 norm = normalize(Normal);//光线角度
        vec3 viewDir = normalize(viewPos - FragPos);//视线角度
        //第一阶段，定向光照
        vec3 result = CalcDirLight(dirLight, norm, viewDir) ;
        //第二阶段，点光源
        for(int i = 0; i<NR_POINT_LIGHTS;i++){
            result += CalcPointLight(pointLights[i], norm, FragPos,viewDir);
        }
        //第三阶段，聚光灯
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
        //混合光照颜色
        FragColor = vec4(result, 1.0);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);//光线向量
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

//可以看出来，点光源与定向光源的区别，点光源要针对每一个像素的位置去计算光线的向量，并且点光源有衰减
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// 聚光灯，集合了内外切衰减，距离衰减
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}