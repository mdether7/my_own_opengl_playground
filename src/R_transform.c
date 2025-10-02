#include "R_transform.h"

const R_Transform R_TRANSFORM_IDENTITY = {
  .position = GLM_VEC3_ZERO,
  .rotation = GLM_VEC3_ZERO,
  .scale    = GLM_VEC3_ONE,
};