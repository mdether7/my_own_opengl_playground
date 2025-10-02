#ifndef R_RENDERER_H
#define R_RENDERER_H

#include "R_camera.h"
#include "E_scene.h"

typedef struct r_renderer_settings_s {
  int wireframe_mode;
} Render_settings;

typedef struct r_renderer_s {

  E_Scene*        scene;
  R_Camera*       camera;

  Render_settings settings;

} R_Renderer;

// returns null on failure
R_Renderer* r_renderer_create(void);
void        r_renderer_destroy(R_Renderer* renderer);

void        r_renderer_set_scene(R_Renderer* renderer, E_Scene* scene);
void        r_renderer_set_camera(R_Renderer* renderer, R_Camera* camera);
void        r_renderer_render_scene(R_Renderer* renderer);
 
#endif