#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   TexCoord = uv;
   gl_Position =  projection*view*model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
