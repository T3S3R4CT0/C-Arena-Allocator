#include "stddef.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
     void* buffer;
     size_t capacity;
     size_t length;
} Arena;

Arena initArena(size_t max_size, void* buffer);
void destroyArena(Arena* self);
void* arena_allocate(Arena* self, size_t bytes, bool* status, char errorBuffer[1024]);
void* arena_allocateAligned(Arena* self, size_t bytes, size_t alignment, bool* status, char errorBuffer[1024]);
void arena_reset(Arena* arena);

#ifdef USING_ARENA

Arena initArena(size_t max_size, void* buffer) {
     return (Arena) {
          .capacity = max_size,
          .length = 0,
          .buffer = buffer
     };
}

void* arena_allocate(Arena* self, size_t bytes, bool* status, char errorBuffer[1024]) {
     auto pointer = self->buffer + self->length;
     self->length += bytes; if (self->length >= self->capacity) {
          *status = true;
          strncpy(errorBuffer, "insufficient memory in arena", 1024);
          return NULL;
     }
     else {
          *status = false;
     }

     return pointer;
}

void* arena_allocateAligned(Arena* self, size_t bytes, size_t alignment, bool* status, char errorBuffer[1024]) {
     auto pointer = self->buffer + self->length;
     self->length += bytes; 

     if (alignment == 0 && alignment % 2 == 1) {
          *status = true;
          strncpy(errorBuffer, "alignment error", 1024);
          return NULL;
     }

     auto padding = bytes % alignment;
     pointer += padding;
     self->length += padding; if (self->length >= self->capacity) {
          *status = true;
          strncpy(errorBuffer, "Insufficient memory in arena", 1024);
          return NULL;
     }
     else {
          *status = false;
     }

     return pointer;
}

void arena_reset(Arena* self) {
     self->length = 0;
}

#endif

