#include "R_camera.h"

#include <stdlib.h>
#include "cglm/call.h"

R_Camera* 
r_camera_create()
{
  R_Camera* camera = malloc(sizeof(*camera));
  if (camera == NULL)
    return NULL;
  
  camera->position[0] = 5.0f;
  camera->position[1] = 0.0f;
  camera->position[2] = 0.0f;

  return camera;
}

void
r_camera_destroy(R_Camera* camera)
{
  if (camera == NULL)
    return;

  free(camera);
}