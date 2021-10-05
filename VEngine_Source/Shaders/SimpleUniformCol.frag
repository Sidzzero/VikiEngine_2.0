#version 330 core
out vec4 FragColor;
uniform vec4 colorToUse;
void main()
{
  FragColor = colorToUse;
}
