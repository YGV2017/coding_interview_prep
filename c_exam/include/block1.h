#ifndef BLOCK1_H
#define BLOCK1_H
#include <stddef.h>
#include <stdint.h>

/* Maximum element; return -1 for NULL or an empty array. */
int max_array(const int *a, size_t n);
/* Reverse a writable NUL-terminated string in place; NULL is a no-op. */
void reverse_string(char *s);
/* Count the set bits in a 32-bit value. */
int count_bits(uint32_t x);
/* Exchange two integers; both pointers must be valid (aliasing is allowed). */
void swap(int *a, int *b);
/* Compact unique values in first-occurrence order; return the prefix length.
 * NULL or an empty array returns 0. The remaining suffix is unspecified. */
size_t remove_duplicates(int *a, size_t n);
#endif
