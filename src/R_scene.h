#ifndef R_SCENE_OBJECTS_H
#define R_SCENE_OBJECTS_H

#include "R_mesh.h"
#include "R_material.h"
#include "R_transform.h"

#include <stddef.h>

#define SCENE_MAX_OBJECTS 100

typedef struct r_scene_s {

  R_Mesh*      meshe;
  R_Material*  materials;
  R_Transform* trasforms;

  unsigned int count;
  unsigned int capacity;

} R_Scene;

#endif