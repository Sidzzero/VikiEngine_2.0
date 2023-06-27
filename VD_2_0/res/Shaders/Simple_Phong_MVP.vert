#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);  // Calculate the final position of the vertex

    FragPos = vec3(model * vec4(aPos, 1.0));  // Transform vertex position to world coordinates

    // Uncomment the line below if scaling is involved in the model transformation
     Normal = mat3(transpose(inverse(model))) * aNormal;

    //Normal = aNormal;       // Pass vertex normal to fragment shader
    TexCoord = aTexCoord;   // Pass texture coordinate to fragment shader
}