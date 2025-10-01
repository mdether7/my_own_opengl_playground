#include "E_grid.h"

#include "H_dims.h"
#include "R_mesh.h"

#include <cglm/call.h>
#include <glad/glad.h>
#include <string.h>
#include <stdlib.h>

void grid_destroy(Grid_object* grid)
{
  if (grid != NULL) {
    free(grid->model_matrices);
    glDeleteBuffers(1, &grid->UBO);
    free(grid);
  }
}

Grid_object* grid_create(Dimensions dims, vec3 star_pos, float spacing, const R_Mesh* primitive)
{
  if (primitive == NULL)
    return NULL;

  if (dimensions_get_volume(dims) > GRID_MAX_SIZE_VOLUME)
    return NULL;
 
  Grid_object* grid = NULL;
  grid = malloc(sizeof(*grid));

  if (grid == NULL)
    return NULL;

  grid->primitive = primitive;
  grid->dims = dims;
  glmc_vec3_copy(star_pos, grid->pos);

  grid->model_matrices = NULL;
  grid->model_matrices = malloc(sizeof(mat4) * (size_t)dimensions_get_volume(dims));

  if (grid->model_matrices == NULL) {
    free(grid);
    return NULL;
  }


  float gap = 1.5f;
  size_t count = 0;
  for (unsigned int i = 0; i < dims.width; i++)
    for (unsigned int j = 0; j < dims.height; j++)
      for (unsigned int k = 0; k < dims.depth; k++) {

        mat4 mat;

        glmc_mat4_identity(mat);
        glmc_translate(mat, (vec3){i*(spacing+gap) - 1.0f, j*(spacing+gap), k*(spacing+gap) + -5.0f});

        memcpy((grid->model_matrices + count), mat, sizeof(mat));
        count++;
        
      }
  
  grid->matrix_count = (size_t)dimensions_get_volume(dims);
  grid->matrix_bytes = grid->matrix_count * sizeof(mat4);

  grid->UBO = 0;
  glGenBuffers(1, &grid->UBO);
  glBindBuffer(GL_UNIFORM_BUFFER, grid->UBO);
  glBufferData(GL_UNIFORM_BUFFER, grid->matrix_bytes, grid->model_matrices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  return grid;
}
