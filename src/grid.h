#ifndef MY_MODEL_H
#define MY_MODEL_H

#include "H_dims.h"
#include "R_mesh.h"

#include <cglm/types.h>
#include <glad/glad.h>
#include <stddef.h>

#define GRID_MAX_SIZE_VOLUME 1000 // 10x10x10

typedef struct object_s Object; // or shoudl i call it primitive?

typedef struct grid_object_s {

  Dimensions       dims;
  vec3             pos;

  const Mesh*      primitive;

  GLuint           UBO; 
  mat4*            model_matrices;
  size_t           matrix_count;    
  size_t           matrix_bytes;

} Grid_object;

// TODO(mdether7): ADD SCALING OR SOME SHIT tO THOSE GRID TYPE OBJECTS

Grid_object* grid_create(Dimensions dims, vec3 star_pos, float spacing, const Mesh* primitive);
void         grid_destroy(Grid_object* grid);



#endif