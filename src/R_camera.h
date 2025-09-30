#ifndef R_CAMERA_H
#define R_CAMERA_H

#include "R_transform.h"

#include "cglm/call.h"

typedef struct r_camera_s {

  R_Transform  transform;

} R_Camera;

#endif