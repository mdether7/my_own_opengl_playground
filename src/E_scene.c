#include "E_scene.h"

#include <stdlib.h>

E_Scene* 
e_scene_create(void)
{
  E_Scene* scene = malloc(sizeof(*scene));

  if (scene == NULL)
    return NULL;

  scene->meshes     = malloc(sizeof(R_Mesh) * SCENE_MAX_OBJECTS);
  scene->materials  = malloc(sizeof(R_Material) * SCENE_MAX_OBJECTS);
  scene->transforms = malloc(sizeof(R_Transform) * SCENE_MAX_OBJECTS);
  
  if ( !scene->meshes || !scene->materials || !scene->transforms ) {
    free(scene->meshes);
    free(scene->materials);
    free(scene->transforms);
    free(scene);
    return NULL;
  }

  scene->count    = 0;
  scene->capacity = SCENE_MAX_OBJECTS;

  return scene;
}


void
e_scene_destroy(E_Scene* scene)
{
  if (scene != NULL) {
    free(scene->meshes);
    free(scene->materials);
    free(scene->transforms);
    scene->count = scene->capacity = 0;
  }  
}