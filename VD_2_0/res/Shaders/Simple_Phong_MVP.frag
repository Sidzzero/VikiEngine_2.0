#version 330 core
out vec4 FragColor;
in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;  
uniform sampler2D ourTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;


void main()
{
    float ambientStrenght = 0.5;
    vec3 ambient = ambientStrenght*lightColor;

    //Diffuse Calcuations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(FragPos - lightPos);
    float diffuseVal = max( dot ( norm , lightDir ),0.0);
    vec3 diffuse = diffuseVal*lightColor;

    vec3 result = (ambient + diffuse)*objectColor;
    FragColor = vec4(result,1.0);
    FragColor = vec4(ambient + diffuse,1.0)*texture(ourTexture, TexCoord);
   // FragColor = vec4(vec3(0.0,1.0,0.0) , 1.0);
    // FragColor = texture(ourTexture, TexCoord);//TODO: Lighting with texture
}