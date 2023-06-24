#version 330 core
out vec4 FragColor;
//in vec2 TexCoord;  
in vec3 Normal;  
uniform sampler2D ourTexture;

uniform vec4 objectColor;
uniform vec4 lightColor;


void main()
{
    float ambientStrenght = 0.5;
   // vec4 ambient = ambientStrenght;//TODO: *lightColor;
    vec4 resultAmbient = ambientStrenght *objectColor;

    FragColor = resultAmbient;
    // FragColor = texture(ourTexture, TexCoord);//TODO: Lighting with texture
}