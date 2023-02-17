#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HEAP_SIZE
#define HEAP_SIZE 0x200
#endif

#ifndef HEAP_DUMP
#define HEAP_DUMP (0)
#endif

void *heap_alloc(size_t size);
void heap_free(void *ptr);
void heap_dump(void);

#ifdef __cplusplus
}
#endif

#endif /* HEAP_H */
