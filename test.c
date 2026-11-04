#define USING_ARENA

#include "arena.h"
#include "string.h"
#include "stdio.h"

const int arena_max_size = 1024 * 1024;

int main() {
     bool err;
     void* arena_buffer = malloc(arena_max_size);
     auto arena = init_arena(arena_max_size, arena_buffer); 

     int* p1 = arena_alloc(&arena, 10 * sizeof(int), &err);

     for (int i = 0; i < 10; i++) {
          p1[i] = i;
          printf("%d\n", p1[i]);
     }
     
     auto len = strlen("hello world");
     char* string = arena_alloc(&arena, len, &err);
     strncpy(string, "hello world", len);
     printf("%s\n", string);
     
     free(arena_buffer);
     return 0;
}
