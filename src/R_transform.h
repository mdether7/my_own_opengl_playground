#ifndef R_TRANSFORM_H
#define R_TRANSFORM_H

#include <cglm/call.h>

typedef struct r_transform_s {
  vec3 position;
  mat4 rotation;
  vec3 scale;
} R_Transform;


#endif