#include "E_primitives.h"

#include "primitives_data/cube.h"
#include "R_mesh.h"

R_Mesh* cube_primitive = NULL;

int  
e_primitives_init(void)
{
  if (r_mesh_create(cube_primitive, cube_attribs, (float*)cube_vertices, cube_indices, 1, 3, 24, 36) < 0)
    return -1;

  return 0;
}

void 
e_primitives_destroy(void)
{
  r_mesh_destroy(cube_primitive);
  cube_primitive = NULL;
}
