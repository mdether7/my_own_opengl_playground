#ifndef MY_MESH_H
#define MY_MESH_H

#include <glad/glad.h>

#include "R_vertex_type.h"
#include <stddef.h>

typedef struct r_mesh_s {

  GLuint                VAO;
  GLuint                VBO;
  GLuint                EBO;
  
  GLenum                index_type;
  GLsizei               index_count;

} R_Mesh;

int
r_mesh_create(R_Mesh*                 mesh,    // object to be created
            const Vertex_attrib*  attribs,     // data of the layout
            const float*          vertex_data,
            const GLuint*       index_data,    // indices
            size_t number_of_attributes,       // length of attribs
            size_t single_vertex_size,       
            size_t num_of_vertices, 
            size_t num_of_indices);

int
r_mesh_bind(const R_Mesh* mesh);

void
r_mesh_unbind(void);

void
r_mesh_destroy(R_Mesh* mesh);

#endif