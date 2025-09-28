#include "grid.h"

#include "dims.h"

#include <cglm/call.h>
#include <string.h>
#include <stdlib.h>

   // WIP WIP SHIT // TENTEN
  // Dimensions       dims;
  // vec3             pos;

  // const Object*    primitives;

  // mat4*            model_matrices;
  // size_t           matrix_count;    
  // size_t           matrix_bytes;

void grid_destroy(Grid_object* grid)
{
  if (grid != NULL) {
    free(grid->model_matrices);
    free(grid);
  }
}

Grid_object* grid_create(Dimensions dims, const vec3 star_pos, float spacing, const Object* primitive)
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


  float gap = 0.0f;
  size_t count = 0;
  for (int i = 0; i < dims.width; i++)
    for (int j = 0; j < dims.height; j++)
      for (int k = 0; k < dims.depth; k++) {

        mat4 mat;

        glmc_mat4_identity(mat);
        glmc_translate(mat, (vec3){i*(spacing+gap), j*(spacing+gap), k*(spacing+gap)});

        memcpy((grid->model_matrices + count), mat, sizeof(mat));
        count++;
        
      }
  
  grid->matrix_count = (size_t)dimensions_get_volume(dims);
  grid->matrix_bytes = grid->matrix_count * sizeof(mat4);

  return grid;
}
