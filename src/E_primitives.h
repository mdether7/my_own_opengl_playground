#ifndef E_PRIMITIVES_H
#define E_PRIMITIVES_H

#include <stddef.h>

// forward declaration fuckery
typedef struct r_mesh_s R_Mesh;

extern R_Mesh* cube;

int  e_primitives_init(void);
void e_primitives_destroy(void);

#endif