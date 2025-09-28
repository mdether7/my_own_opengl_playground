#include "grid.h"

#include "dims.h"

#include <cglm/call.h>
#include <stdlib.h>

Grid_object* grid_create(Dimensions dims, const vec3 star_pos, const Object* primitive)
{
  if (primitive == NULL)
    return NULL;
 
  Grid_object* grid = malloc(sizeof(*grid));

  if (grid == NULL)
    return NULL;

  grid->primitive = primitive;
  grid->dims = dims;
  grid->pos[0] = star_pos[0];
  grid->pos[1] = star_pos[1];
  grid->pos[2] = star_pos[2];

  grid->model_matrices = NULL;
  grid->model_matrices = malloc(sizeof(mat4) * (size_t)dimensions_get_volume(dims));

  if (grid->model_matrices = NULL)
    return NULL;

  




  
}

  // Dimensions       dims;
  // vec3             pos;

  // const Object*    primitives;

  // mat4*            model_matrices;
  // size_t           matrix_count;    
  // size_t           matrix_bytes;