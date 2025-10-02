#ifndef MY_SHADER_H
#define MY_SHADER_H

#include "R_shader_type.h"

#include <cglm/types.h>

R_Shader_program* r_shader_create(const char* vert_path, const char* frag_path);

void r_shader_destroy(R_Shader_program* program);

void r_shader_bind(R_Shader_program* program);

void r_shader_send_uniform_vec3(R_Shader_program* program, unsigned int count, float* v, const char* uniform_name);
void r_shader_send_uniform_mat4(R_Shader_program* program, mat4 m, const char* uniform_name);
void r_shader_send_uniform_int(R_Shader_program* program, int b, const char* uniform_name);

#endif