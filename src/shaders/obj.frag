#version 330 core
out vec4 FragColor;
in vec3 NormalPos; //法线向量
in vec3 FragPos;//世界坐标系向量

uniform vec3 lightColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    //法线单位向量
    vec3 nor = normalize(NormalPos);
    //环境光
    vec3 ambient =  lightColor * material.ambient;
    //漫反射
    vec3 lightV = normalize(lightPos - FragPos);
    float diff = max(dot(nor, lightV),0.0);
    vec3 diffuse =  lightColor * (diff * material.diffuse);
    //镜面反射
    vec3 viewV = normalize(viewPos - FragPos);
    vec3 reflectLight = reflect(-lightV, nor);
    float spec = pow(max(dot(reflectLight, viewV),0.0),material.shininess);
    vec3 specular =  lightColor * (spec * material.specular);

    FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0);
}