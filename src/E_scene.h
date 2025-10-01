#ifndef E_SCENE_H
#define E_SCENE_H

#include "R_mesh.h"
#include "R_material.h"
#include "R_transform.h"

#include <stddef.h>

#define SCENE_MAX_OBJECTS 1000

typedef struct e_scene_s {

  // ecs style objects
  R_Mesh*      meshes;
  R_Material*  materials;
  R_Transform* transforms;

  unsigned int count;
  unsigned int capacity;

} E_Scene;

E_Scene* r_scene_create(void);

#endif
