#version 460 core

layout (location = 0) in vec3 attribute_pos;
layout (location = 1) in vec3 attribute_color;

layout (std140) uniform Matrices
{
  mat4 model_grid[1000];
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int debug_color_flag;
uniform vec3 debug_color_array[6];

out vec3 color_from_vert;

void main()
{
  mat4 model = model_grid[gl_InstanceID];

  vec4 original_position = vec4(attribute_pos.x, attribute_pos.y, attribute_pos.z, 1.0f);
  gl_Position = projection * view * model * original_position;

  if (debug_color_flag == 1) 
  {
    color_from_vert = debug_color_array[gl_VertexID / 4];
  } 
  else
  {
    color_from_vert = attribute_color;
  }

}