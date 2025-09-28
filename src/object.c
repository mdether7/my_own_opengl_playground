#include "object.h"
#include "vertex_type.h"

#include <glad/glad.h>
#include <stddef.h>
#include <assert.h>

int
object_create(Object*               obj,
              const Shader_program* program,
              const Vertex_attrib*  attribs,
              const float*          vertex_data,
              const GLushort*       index_data,
              size_t number_of_attributes,
              size_t single_vertex_size,
              size_t num_of_vertices,
              size_t num_of_indices)
{
  if (!obj || !program || !attribs || !vertex_data || !index_data)
      return -1;

  obj->VAO = 0;
  obj->VBO = 0;
  obj->EBO = 0;
  obj->shader = NULL;

  // BIND GEN AND BIND VAO
  glGenVertexArrays(1, &obj->VAO);
  glBindVertexArray(obj->VAO);
  //

  size_t vertex_data_size = single_vertex_size * num_of_vertices * sizeof(float);

  glGenBuffers(1, &obj->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
  glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

  GLint size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if(vertex_data_size != (size_t)size)
  {
    glDeleteVertexArrays(1, &obj->VAO);
    glDeleteBuffers(1, &obj->VBO);
    glDeleteBuffers(1, &obj->EBO);
    obj->VBO = obj->EBO = obj->VAO = 0;
    return -1;
  }

  size_t index_data_size = num_of_indices * sizeof(GLushort);

  glGenBuffers(1, &obj->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data_size, index_data, GL_STATIC_DRAW);

  size = 0;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if(index_data_size != (size_t)size)
  {
    glDeleteVertexArrays(1, &obj->VAO);
    glDeleteBuffers(1, &obj->VBO);
    glDeleteBuffers(1, &obj->EBO);
    obj->VBO = obj->EBO = obj->VAO = 0;
    return -1;
  }

  for (size_t i = 0; i < number_of_attributes; i++) {
    glEnableVertexAttribArray(attribs[i].location);
    glVertexAttribPointer(attribs[i].location, // dot has predesesen over *
                          attribs[i].components,
                          GL_FLOAT,
                          GL_FALSE,
                          (GLsizei)(sizeof(GLfloat) * single_vertex_size),
                          (void*)(attribs[i].offset * sizeof(float)));
  }

  obj->shader = program;

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Do NOT unbind ELEMENT_ARRAY_BUFFER after VAO is unbound
  // because the VAO stores that EBO binding internally
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return 0;
}

void
object_destroy(Object* obj)
{
// glGenBuffers(1, &obj->VBO);     // Generate - pass by address
// glDeleteBuffers(1, &obj->VBO);  // Delete - pass by address 
// glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);  // Bind - pass by value
  if (obj != NULL) {

    glDeleteVertexArrays(1, &obj->VAO);
    glDeleteBuffers(1, &obj->VBO);
    glDeleteBuffers(1, &obj->EBO);

    obj->VBO = obj->EBO = obj->VAO = 0;
    obj->shader = NULL;

  }
  
}

int
object_bind(Object* obj)
{
  glBindVertexArray(obj->VAO);
  return 0;
}