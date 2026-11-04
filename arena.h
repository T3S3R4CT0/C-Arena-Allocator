#include "stddef.h"
#include "stdlib.h"

typedef struct {
     size_t max_size;
     size_t capacity;
     void* buffer;
} Arena;

Arena init_arena(size_t max_size, void* buffer);
void destroy_arena(Arena* self);
void* arena_alloc(Arena* self, size_t bytes, bool* err);
void* arena_alloc_aligned(Arena* self, size_t bytes, size_t alignment, bool* err);
void arena_reset(Arena* arena);

#ifdef USING_ARENA

Arena init_arena(size_t max_size, void* buffer) {
     return (Arena) {
          .max_size = max_size,
          .capacity = 0,
          .buffer = buffer
     };
}

void* arena_alloc(Arena* self, size_t bytes, bool* err) {
     auto pointer = self->buffer + self->capacity;
     self->capacity += bytes; if (self->capacity >= self->max_size) {
          *err = true;
          return NULL;
     }
     else {
          *err = false;
     }

     return pointer;
}

void* arena_alloc_aligned(Arena* self, size_t bytes, size_t alignment, bool* err) {
     auto pointer = self->buffer + self->capacity;
     self->capacity += bytes; 

     if (alignment == 0 && alignment % 2 == 1) {
          *err = true;
          return NULL;
     }

     const auto padding = bytes % alignment;
     pointer += padding;
     self->capacity += padding;

     if (self->capacity >= self->max_size) {
          *err = true;
          return NULL;
     }
     else {
          *err = false;
     }

     return pointer;
}

void arena_reset(Arena* self) {
     self->capacity = 0;
}

#endif
