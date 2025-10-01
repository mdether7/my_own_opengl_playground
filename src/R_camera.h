#ifndef R_CAMERA_H
#define R_CAMERA_H

#include "cglm/call.h"

  // MATRIX CHEAT SHEET
  // [00 10 20 30]
  // [01 11 21 31]
  // [02 12 22 32]
  // [03 13 23 33]

typedef struct r_camera_s {
  mat4 view;
  mat4 projection;
  vec3 position;
  vec3 target;
} R_Camera;

#endif