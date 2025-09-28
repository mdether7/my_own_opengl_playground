#ifndef MY_MODEL_H
#define MY_MODEL_H

#include "dims.h"

#include <cglm/types.h>
#include <stddef.h>

#define GRID_MAX_SIZE_VOLUME 1000 // 10x10x10

typedef struct object_s Object; // or shoudl i call it primitive?

typedef struct grid_object_s {

  Dimensions       dims;
  vec3             pos;

  const Object*    primitive;

  mat4*            model_matrices;
  size_t           matrix_count;    
  size_t           matrix_bytes;

} Grid_object;

// TODO(mdether7): ADD SCALING OR SOME SHIT tO THOSE GRID TYPE OBJECTS

Grid_object* grid_create(Dimensions dims, const vec3 star_pos, float spacing, const Object* primitive);
void         grid_resize(Grid_object* grid, vec3 dims);
void         grid_destroy(Grid_object* grid);



#endif