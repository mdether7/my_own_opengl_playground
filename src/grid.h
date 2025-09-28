#ifndef MY_MODEL_H
#define MY_MODEL_H

#include <cglm/types.h>
#include <stddef.h>

typedef struct object_s Object; // or shoudl i call it primitive?

typedef struct grid_object_s {

  const Object*    primitives;

  mat4*            model_matrices;
  size_t           matrix_count;    
  size_t           matrix_bytes;
      
  vec3             dimensions;
  vec3             position;

} Grid_object;

// TODO(mdether7): ADD SCALING OR SOME SHIT tO THOSE GRID TYPE OBJECTS

Grid_object* grid_create(const vec3 dims, const vec3 star_pos, const Object* primitive);
void         grid_resize(Grid_object* grid, vec3 dims);
void         grid_destroy(Grid_object* grid);



#endif