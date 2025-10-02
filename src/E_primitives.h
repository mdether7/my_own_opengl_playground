#ifndef E_PRIMITIVES_H
#define E_PRIMITIVES_H

typedef struct e_object_s E_Object;

E_Object* e_primitives_create_cube();
void e_primitives_destroy_cube(E_Object* cube);

#endif