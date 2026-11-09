#define USING_ARENA

#include "arena.h"
#include "string.h"
#include "stdio.h"

const int arenaMaxSize = 1024 * 1024 * 1024;

int main() {
     bool status;
     char errorBuffer[1024];

     auto arenaBuffer = malloc(arenaMaxSize);

     auto arena = initArena(arenaMaxSize, arenaBuffer);

     int* p1 = arena_allocateAligned(&arena, 100 * sizeof(int), alignof(int), &status, errorBuffer);
     float* p2 = arena_allocateAligned(&arena, 69 * sizeof(float), alignof(float), &status, errorBuffer);
     
     for (int i = 0; i < 100; i++) {
          p1[i] = i * 2;
          printf("p1[%d] = %d\n", i, p1[i]);
     }

     for (int i = 0; i< 69; i++) {
          p2[i] = i / 1.5 * i;
          printf("p2[%d] = %f\n", i, p2[i]);
     }

     arena_reset(&arena);
     
     size_t length = strlen("hello world");
     char* p3 = arena_allocate(&arena, length, &status, errorBuffer); if (status) {
          fprintf(stderr, "Error at allocating string\n");
          return 1;
     }
     strncpy(p3, "hello world", length);

     printf("p3 = %s", p3);

     free(arenaBuffer);
     return 0;
}
