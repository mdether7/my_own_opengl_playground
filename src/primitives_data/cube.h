#ifndef MY_CUBE_H
#define MY_CUBE_H

#include "../R_vertex_type.h"
#include "glad/glad.h"

static const Vertex cube_vertices[] = {
  // front face
  {{-0.5f, -0.5f,  0.5f}}, // 0
  {{ 0.5f, -0.5f,  0.5f}}, // 1
  {{ 0.5f,  0.5f,  0.5f}}, // 2
  {{-0.5f,  0.5f,  0.5f}}, // 3

  // back face
  {{-0.5f, -0.5f, -0.5f}}, // 4
  {{ 0.5f, -0.5f, -0.5f}}, // 5
  {{ 0.5f,  0.5f, -0.5f}}, // 6
  {{-0.5f,  0.5f, -0.5f}}, // 7

  // top face 
  {{-0.5f,  0.5f,  0.5f}}, // 8  
  {{ 0.5f,  0.5f,  0.5f}}, // 9    
  {{ 0.5f,  0.5f, -0.5f}}, // 10
  {{-0.5f,  0.5f, -0.5f}}, // 11

  // bottom face
  {{-0.5f, -0.5f, -0.5f}}, // 12  
  {{ 0.5f, -0.5f, -0.5f}}, // 13   
  {{ 0.5f, -0.5f,  0.5f}}, // 14
  {{-0.5f, -0.5f,  0.5f}}, // 15

  // right face 
  {{ 0.5f, -0.5f,  0.5f}}, // 16   
  {{ 0.5f, -0.5f, -0.5f}}, // 17   
  {{ 0.5f,  0.5f, -0.5f}}, // 18
  {{ 0.5f,  0.5f,  0.5f}}, // 19

  // left face
  {{-0.5f, -0.5f, -0.5f}}, // 20   
  {{-0.5f, -0.5f,  0.5f}}, // 21  
  {{-0.5f,  0.5f,  0.5f}}, // 22
  {{-0.5f,  0.5f, -0.5f}}, // 23
};

static const GLuint cube_indices[] = {
  // front face
  0, 2, 3,
  2, 0, 1,
  // back face
  4, 7, 6,
  6, 5, 4,
  // top face
  11, 8, 9,
  10, 11, 9,
  // bottom face
  12, 14, 15,
  13, 14, 12,
  // right face
  19, 16, 17,
  18, 19, 17,
  // left face
  22, 23, 21,
  23, 20, 21,
};

static Vertex_attrib cube_attribs[] = {
  {0, 3, 0},
};

#endif