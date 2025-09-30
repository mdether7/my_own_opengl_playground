#ifndef MY_DIMS_H
#define MY_DIMS_H

typedef struct dimensions_s {
  unsigned int width;
  unsigned int height;
  unsigned int depth;
} Dimensions;

unsigned int dimensions_get_volume(const Dimensions dims);

#endif