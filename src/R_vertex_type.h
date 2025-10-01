#ifndef MY_VERTEX_H
#define MY_VERTEX_H

#include <cglm/types.h>

typedef struct vertex_s {

  vec3 position;
  
} Vertex;

typedef struct vertex_attrib_s {

  int location;      // attribute location (0, 1, 2...)

  int components;    // how many floats (3 for xyz, 2 for uv etc...)

  int offset;        // offset in floats from start of vertex

} Vertex_attrib;

#endif