#include "h_dims.h"

unsigned int dimensions_get_volume(const Dimensions dims)
{
  return dims.width * dims.height * dims.depth;
}