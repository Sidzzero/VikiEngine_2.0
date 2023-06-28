#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
  vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;  
uniform sampler2D ourTexture;

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    float ambientStrenght = 0.2;
    vec3 ambient = material.ambient*light.ambient;

    //Diffuse Calcuations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( light.position - FragPos);
    float diffuseVal = max( dot ( norm , lightDir ),0.0);
    vec3 diffuse = (material.diffuse*diffuseVal)*light.diffuse;

    //Spectualr
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  (spec*material.specular) * light.specular; 

    FragColor = vec4(ambient + diffuse+ specular,1.0);//*texture(ourTexture, TexCoord);
 
}