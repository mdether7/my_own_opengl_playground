#ifndef R_CAMERA_H
#define R_CAMERA_H

#include "cglm/call.h"

  // MATRIX CHEAT SHEET
  // [00 10 20 30]
  // [01 11 21 31]
  // [02 12 22 32]
  // [03 13 23 33]

typedef struct r_camera_s {
  vec3 position;
} R_Camera;

R_Camera* r_camera_create();
void      r_camera_destroy(R_Camera* camera);

#endif