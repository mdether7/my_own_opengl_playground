#ifndef R_SCENE_OBJECTS_H
#define R_SCENE_OBJECTS_H

#include "R_mesh.h"

#include <stddef.h>

typedef struct r_object_s {

  R_Mesh*      mesh;

} R_Object;

typedef struct r_scene_s {

  R_Object*    objects;
  size_t       size_in_bytes;

} R_Scene;

#endif