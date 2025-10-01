#ifndef R_TEXTURE_H
#define R_TEXTURE_H

typedef enum {
  
  TEXTURE_DEFAULT = 0,
  TEXTURE_GRASS,
  TEXTURE_MOONROCK,
  TEXTURE_TOTAL,

} texture_type;

int texture_load(const char* filepath);

#endif