#ifndef MY_SHADER_H
#define MY_SHADER_H

#include "shader_type.h"

#include <cglm/types.h>

typedef unsigned int GLuint;

int
shader_create(Shader_program* program, const char* vert_path, const char* frag_path);
void 
shader_destroy(Shader_program* program);
void 
shader_bind(Shader_program* program);
void
shader_send_uniform_vec3(Shader_program* program, unsigned int count, float* v, const char* uniform_name);
void
shader_send_uniform_mat4(Shader_program* program, mat4 m, const char* uniform_name);
void
shader_send_uniform_int(Shader_program* program, int b, const char* uniform_name);



#endif