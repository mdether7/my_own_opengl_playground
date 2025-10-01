#ifndef R_SCENE_OBJECTS_H
#define R_SCENE_OBJECTS_H

#include "R_mesh.h"
#include "R_material.h"
#include "R_transform.h"

#include <stddef.h>

#define SCENE_MAX_OBJECTS 1000

typedef struct r_scene_s {

  // ecs style objects
  R_Mesh*      meshes;
  R_Material*  materials;
  R_Transform* trasforms;

  unsigned int count;
  unsigned int capacity;

} R_Scene;

#endif
