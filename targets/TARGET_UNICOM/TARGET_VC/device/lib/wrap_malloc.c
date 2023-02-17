#include <reent.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "heap.h"

void *__wrap__malloc_r(struct _reent *ptr, size_t size)
{
    (void) ptr;
    return heap_alloc(size);
}

void __wrap__free_r(struct _reent *ptr, void *addr)
{
    (void) ptr;
    heap_free(addr);
}

void *__wrap__realloc_r(struct _reent *ptr, void *mem, size_t newsize)
{
    if (newsize == 0) {
        heap_free(mem);
        return NULL;
    }

    void *p;
    p = heap_alloc(newsize);
    if (p) {
        if (mem != NULL) {
            memcpy(p, mem, newsize);
            heap_free(mem);
        }
    }
    return p;
}

void *__wrap__calloc_r(struct _reent *ptr, size_t size, size_t len)
{
    void *mem;
    mem = heap_alloc(size*len);
    memset(mem, 0, (size*len));
    return mem;
}
