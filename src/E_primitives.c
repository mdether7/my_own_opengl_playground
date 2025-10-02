#include "E_primitives.h"

#include "primitives_data/cube.h"
#include "R_mesh.h"
#include "R_material.h"
#include "R_transform.h"
#include "E_object.h"

E_Object*
e_primitives_create_cube()
{
  R_Mesh cube_mesh;

  if (r_mesh_create(&cube_mesh,
                    cube_attribs,
                    (float*)cube_vertices,
                    cube_indices, 1, 3, 24, 36) < 0)
  return NULL;

  E_Object* cube = malloc(sizeof(*cube));
  if (cube == NULL) {
    r_mesh_destroy(&cube_mesh);
    return NULL;
  }

  cube->mesh = cube_mesh;
  cube->material = (R_Material){0};
  cube->transform = R_TRANSFORM_IDENTITY;

  return cube;
}

void 
e_primitives_destroy_cube(E_Object* cube)
{
  if (cube == NULL) 
    return;
  r_mesh_destroy(&cube->mesh);
  free(cube);
}

