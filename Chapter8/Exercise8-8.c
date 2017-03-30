/**
 * Write a routine bfree(p, n) that will free any arbitrary block p of n characters
 * into the free list maintained by malloc and free. By using bfree, a user can add
 * a static or eternal array to the free list at any time.
 */

/* bfree: add an arbitrary block p of n characters into free list */
void bfree(void* p, size_t n) {
    Header *up;

    up = (Header *) p;
    up->s.size = n - sizeof(Header);
    free((void *)(up+1)); /* calling free inserts this prepped block into the free list */
}