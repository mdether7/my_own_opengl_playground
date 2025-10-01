#ifndef E_OBJECT_H
#define E_OBJECT_H

#include "R_mesh.h"
#include "R_material.h"
#include "R_transform.h"

typedef struct e_object_s {
  R_Mesh      mesh;
  R_Material  material;
  R_Transform transform;
} E_Object;

#endif