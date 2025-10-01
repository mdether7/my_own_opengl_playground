#include "E_scene.h"
#include "E_object.h"

#include <stdlib.h>

void
e_scene_add_object(E_Scene* scene, E_Object object)
{
  if (scene == NULL) 
    return;

  if (scene->count >= scene->capacity)
    return;

  scene->meshes[scene->count] = object.mesh;
  scene->materials[scene->count] = object.material;
  scene->transforms[scene->count] = object.transform;
  scene->count++;
}

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

    // cleanup mesh/materials/transforms in a loop

    free(scene->meshes);
    free(scene->materials);
    free(scene->transforms);
    free(scene);
  }  
}