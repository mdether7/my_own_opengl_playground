#ifndef R_TRANSFORM_H
#define R_TRANSFORM_H

#include <cglm/call.h>

typedef struct r_transform_s {
  vec3 position; // easy enough
  vec3 rotation; // each component stores rotation for individual AXIS
  vec3 scale;    // easy enough
} R_Transform;

extern const R_Transform R_TRANSFORM_IDENTITY;

#endif