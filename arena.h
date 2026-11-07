#include "stddef.h"
#include "stdlib.h"

typedef struct {
     void* buffer;
     size_t capacity;
     size_t length;
} Arena;

Arena initArena(size_t max_size, void* buffer);
void destroyArena(Arena* self);
void* arena_allocate(Arena* self, size_t bytes, bool* error);
void* arena_allocateAligned(Arena* self, size_t bytes, size_t alignment, bool* error);
void arena_reset(Arena* arena);

#ifdef USING_ARENA

Arena initArena(size_t max_size, void* buffer) {
     return (Arena) {
          .capacity = max_size,
          .length = 0,
          .buffer = buffer
     };
}

void* arena_allocate(Arena* self, size_t bytes, bool* error) {
     auto pointer = self->buffer + self->length;
     self->length += bytes; if (self->length >= self->capacity) {
          *error = true;
          return NULL;
     }
     else {
          *error = false;
     }

     return pointer;
}

void* arena_allocateAligned(Arena* self, size_t bytes, size_t alignment, bool* error) {
     auto pointer = self->buffer + self->length;
     self->length += bytes; 

     if (alignment == 0 && alignment % 2 == 1) {
          *error = true;
          return NULL;
     }

     auto padding = bytes % alignment;
     pointer += padding;
     self->length += padding;

     if (self->length >= self->capacity) {
          *error = true;
          return NULL;
     }
     else {
          *error = false;
     }

     return pointer;
}

void arena_reset(Arena* self) {
     self->length = 0;
}

#endif

