#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include "shader_type.h"
#include "vertex_type.h"
#include <stddef.h>

typedef struct object_s {

  GLuint                VAO;
  const Shader_program* shader; // MATERIAL BETTER

  GLuint                VBO;
  GLuint                EBO; 

} Object;

int
object_create(Object*               obj,        // object to be created
              const Shader_program* program,    // shader associated with object
              const Vertex_attrib*  attribs,    // data of the layout
              const float*          vertex_data,
              const GLushort*       index_data, // indices
              size_t number_of_attributes,      // length of attribs
              size_t single_vertex_size,       
              size_t num_of_vertices, 
              size_t num_of_indices); 

void
object_destroy(Object* obj);

int
object_bind(Object* obj);


#endif