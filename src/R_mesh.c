#include "R_mesh.h"
#include "R_vertex_type.h"

#include <glad/glad.h>
#include <stddef.h>
#include <assert.h>

int
r_mesh_create(R_Mesh*                 mesh,
            const Vertex_attrib*  attribs,
            const float*          vertex_data,
            const GLuint*       index_data,
            size_t number_of_attributes,
            size_t single_vertex_size,
            size_t num_of_vertices,
            size_t num_of_indices)
{
  if (!mesh || !attribs || !vertex_data || !index_data)
      return -1;

  mesh->VAO = 0;
  mesh->VBO = 0;
  mesh->EBO = 0;
  mesh->index_type = 0;
  mesh->index_count = 0;

  // GENERATE AND BIND VAO
  glGenVertexArrays(1, &mesh->VAO);
  glBindVertexArray(mesh->VAO);
  //

  // calculate size in bytes of total vertecies
  size_t vertex_data_size = single_vertex_size * num_of_vertices * sizeof(float);

  glGenBuffers(1, &mesh->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

  GLint size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if(vertex_data_size != (size_t)size)
  {
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    mesh->VBO = mesh->EBO = mesh->VAO = 0;
    return -1;
  }

  size_t index_data_size = num_of_indices * sizeof(GLuint);

  glGenBuffers(1, &mesh->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data_size, index_data, GL_STATIC_DRAW);

  size = 0;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if(index_data_size != (size_t)size)
  {
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    mesh->VBO = mesh->EBO = mesh->VAO = 0;
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

  mesh->index_type = GL_UNSIGNED_INT;
  mesh->index_count = num_of_indices;

  glBindVertexArray(0);

  return 0;
}

int
r_mesh_bind(const R_Mesh* mesh)
{
  glBindVertexArray(mesh->VAO);
  return 0;
}

void
r_mesh_unbind(void)
{
  glBindVertexArray(0);
}

void
r_mesh_destroy(R_Mesh* mesh)
{
// glGenBuffers(1, &obj->VBO);     // Generate - pass by address
// glDeleteBuffers(1, &obj->VBO);  // Delete - pass by address 
// glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);  // Bind - pass by value
  if (mesh != NULL) {

    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);

    mesh->VBO = mesh->EBO = mesh->VAO = 0;
    mesh->index_type = mesh->index_count = 0;

  }
  
}