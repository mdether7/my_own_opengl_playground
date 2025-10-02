#ifndef G_CHUNK_H
#define G_CHUNK_H

#define CHUNK_SIZE_X 8
#define CHUNK_SIZE_Y 8
#define CHUNK_SIZE_Z 64

typedef enum { AIR = 0, SOLID } block_type;

typedef struct g_chunk_s {

  block_type blocks
  [CHUNK_SIZE_X]
  [CHUNK_SIZE_Y]
  [CHUNK_SIZE_Z];  
  
} G_Chunk;


#endif