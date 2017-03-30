/** 
 * The standard library function calloc(n, size) returns a pointer to n objects of
 * size size, with the storage initialized to zero. Write calloc, by calling malloc or by
 * modifying it.
 */

extern void* malloc(size_t size);
extern void* memset(void* ptr, int value, size_t num);

void* calloc(size_t num, size_t size) {
    void* mem = malloc(num * size);
    if (mem == NULL) return NULL;
    memset(mem, 0, num * size);
    return mem;
}