#ifndef R_RENDERER_H
#define R_RENDERER_H

#include "R_camera.h"
#include "R_scene.h"

typedef struct r_renderer_settings_s {
} Render_settings;

typedef struct r_renderer_s {

  R_Scene*        scene;
  R_Camera*       camera;

  Render_settings settings;

} R_Renderer;

// returns null on failure
R_Renderer* r_renderer_create(R_Renderer* renderer);
void        r_renderer_destroy(R_Renderer* renderer);

void        r_renderer_render_scene(R_Renderer* renderer);
 



#endif