#version 460 core

out vec4 FRAGMENT_COLOR;

in vec3 color_from_vert;

void main()
{
  FRAGMENT_COLOR = vec4(color_from_vert, 1.0f);
}