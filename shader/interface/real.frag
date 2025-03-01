#version 330 core

in VS_OUT
{
    in vec3 FragPos;
    in vec3 Normal;
    in vec2 TexCoords;
}
fs_in;

uniform vec3 viewPos;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

// 定向光
struct DirectionLight
{
    vec3 dir;        // 方向
    vec3 color;      // 颜色
    float intensity; // 强度
};

uniform DirectionLight directionLight;

// 点光源
struct SpotLight
{
    vec3 position;
    vec3 color;
    vec3 ambient;

    // 衰减参数
    float constant;
    float linear;
    float quadratic;
};

uniform SpotLight spotLight;


vec3 GetDirectionalLight()
{
    vec3 FragPos = fs_in.FragPos;
    vec3 Normal = fs_in.Normal;
    vec2 TexCoords = fs_in.TexCoords;


    // 定向光
    vec3 dirLightDir = normalize(-directionLight.dir);

    // 环境光
    vec3 ambient =
        directionLight.intensity * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(dirLightDir - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionLight.color * diff *
                   vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-dirLightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directionLight.color * spec *
                    vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 GetSpotLightColor()
{
    vec3 FragPos = fs_in.FragPos;
    vec3 Normal = fs_in.Normal;
    vec2 TexCoords = fs_in.TexCoords;

    // 衰减系数
    float distance = length(spotLight.position - FragPos);
    float attenuation =
        1.0 / (spotLight.constant + spotLight.linear * distance +
               spotLight.quadratic * (distance * distance));

    // 环境光
    vec3 ambient =
        spotLight.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =
        spotLight.color * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
        spotLight.color * spec * vec3(texture(material.specular, TexCoords));

    vec3 result = (ambient + diffuse + specular) * attenuation;
    return result;
}

void main()
{
    vec3 result = vec3(0, 0, 0);
    result += GetDirectionalLight();
    result += GetSpotLightColor();
    gl_FragColor =
        vec4(result,
             texture(material.diffuse, fs_in.TexCoords).a); // 不透明度取diffuse纹理的
}