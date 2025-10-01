#ifndef R_TRANSFORM_H
#define R_TRANSFORM_H

#include <cglm/call.h>

typedef struct r_transform_s {
  vec3 position;
  vec3 rotation;
  vec3 scale;
} R_Transform;


#endif