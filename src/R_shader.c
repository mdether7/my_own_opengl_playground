#include "R_shader.h"
#include "utils/file_read.h"

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static int
shader_check_for_error(GLuint object_id, 
                       void (*get_status)(GLuint, GLenum, GLint*),
                       void (*get_log)(GLuint, GLsizei, GLsizei*, GLchar*),
                       GLenum status_param);

static int 
shader_compile_error(GLuint shader);
static int 
shader_program_link_error(GLuint program);

int
shader_create(Shader_program* program, const char* vert_path, const char* frag_path)
{
  program->ID = 0;
  char*         vertex_source;
  char*         fragment_source;

  vertex_source = read_file(vert_path);

  if (vertex_source == NULL)
    return -1;

  fragment_source = read_file(frag_path);
  
  if (fragment_source == NULL) {
    free(vertex_source);
    return -1;
  }

  GLuint vertex_shader_object   = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex_shader_object, 1, (const GLchar* []){vertex_source}, NULL);
  glShaderSource(fragment_shader_object, 1, (const GLchar* []){fragment_source}, NULL);

  free(vertex_source);
  free(fragment_source);

  glCompileShader(vertex_shader_object);
  glCompileShader(fragment_shader_object);

  if (shader_compile_error(vertex_shader_object) < 0 ||
      shader_compile_error(fragment_shader_object) < 0) {

    glDeleteShader(vertex_shader_object);  
    glDeleteShader(fragment_shader_object);

    return -1;
  }

  program->ID = glCreateProgram();

  glAttachShader(program->ID, vertex_shader_object);
  glAttachShader(program->ID, fragment_shader_object);

  glLinkProgram(program->ID);

  if (shader_program_link_error(program->ID) < 0) {

    glDeleteShader(vertex_shader_object);  
    glDeleteShader(fragment_shader_object);

    return -1;
  }

  glDeleteShader(vertex_shader_object);
	glDeleteShader(fragment_shader_object); 

  return 0;
}

void 
shader_destroy(Shader_program* program)
{
  if (program == NULL)
    return;

  glDeleteProgram(program->ID);
  program->ID = 0;
}

void 
shader_bind(Shader_program* program)
{
  assert(program != NULL);
  glUseProgram(program->ID);
}

void
shader_send_uniform_vec3(Shader_program* program, unsigned int count, float* v, const char* uniform_name)
{
  glUniform3fv(glGetUniformLocation(program->ID, uniform_name), count, v);
}

void
shader_send_uniform_mat4(Shader_program* program, mat4 m, const char* uniform_name)
{
  glUniformMatrix4fv(glGetUniformLocation(program->ID, uniform_name), 1, GL_FALSE, &m[0][0]);
}

void
shader_send_uniform_int(Shader_program* program, int value, const char* uniform_name)
{
  glUniform1i(glGetUniformLocation(program->ID, uniform_name), value);
}

static int 
shader_compile_error(GLuint shader)
{
	GLint success;
	char info_log[1024] = {0};

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
		fprintf(stderr, "SHADER ERROR! Log: %s\n", info_log);
		return -1;
	}
	return 0;
}

static int
shader_check_for_error(GLuint object_id, 
                       void (*get_status)(GLuint, GLenum, GLint*),
                       void (*get_log)(GLuint, GLsizei, GLsizei*, GLchar*),
                       GLenum status_param)
{
  GLint status;
  char info_log[1024] = {0};

  get_status(object_id, status_param, &status);
  if (!status) {
    get_log(object_id, sizeof(info_log), NULL, info_log);
    fprintf(stderr, "SHADER ERROR! Log: %s\n", info_log);
    return -1;
  }
  return 0;
}

static int 
shader_program_link_error(GLuint program)
{
  GLint success;
  char info_log[1024] = {0};

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, sizeof(info_log), NULL, info_log);
    fprintf(stderr, "SHADER ERROR! Log: %s\n", info_log);
    return -1;
  }
  return 0;
}
