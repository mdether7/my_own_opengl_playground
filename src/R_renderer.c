#include "R_renderer.h"

#include <assert.h>

static const Render_settings default_setting = {
  .wireframe_mode = 1,
};

R_Renderer* 
r_renderer_create(void)
{
  R_Renderer* renderer = malloc(sizeof(*renderer));
  if (renderer == NULL)
    return NULL;

  renderer->scene  = NULL;
  renderer->camera = NULL;
  renderer->settings = default_setting;

  return renderer;
}

void 
r_renderer_destroy(R_Renderer* renderer)
{
  if (renderer == NULL)
    return;

  free(renderer);
}

void 
r_renderer_set_scene(R_Renderer* renderer, E_Scene* scene)
{
  assert(renderer != NULL);
  assert(scene != NULL);

  if (renderer == NULL || scene == NULL)
    return;
  
  renderer->scene = scene;
}

void 
r_renderer_set_camera(R_Renderer* renderer, R_Camera* camera)
{
  assert(renderer != NULL);
  assert(camera != NULL);

  if (renderer == NULL || camera == NULL)
    return;

  renderer->camera = camera;
}

void 
r_renderer_render_scene(R_Renderer* renderer)
{
  assert(renderer != NULL);
  assert(renderer->scene != NULL);
  assert(renderer->camera != NULL);

  if (!renderer || !renderer->scene || !renderer->camera)
    return;

    




}