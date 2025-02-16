#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
in vec2 TexCoords;

struct Light
{
    vec3 direction;             // 定向光
    vec3 directionalColor;      // 定向光颜色
    float directionalIntensity; // 定向光强度
    vec3 position;
    vec3 ambient;
    vec3 color;
};

uniform Light light;

void main()
{
    // // 环境光
    // vec3 ambient = light.ambient * vec3(texture(material.diffuse,
    // TexCoords));

    // // 漫反射
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse =
    //     light.color * diff * vec3(texture(material.diffuse, TexCoords));

    // // 镜面光
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular =
    //     light.color * spec * vec3(texture(material.specular, TexCoords));

    // vec3 result = ambient + diffuse + specular;
    // FragColor = vec4(result, 1.0);

    vec3 dirLightDir = normalize(-light.direction);

    // 环境光
    vec3 ambient = light.directionalIntensity * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(dirLightDir - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =
        light.directionalColor * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-dirLightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =
        light.directionalColor * spec * vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}