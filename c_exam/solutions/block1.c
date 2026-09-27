#include "block1.h"
#include <string.h>
#include <stdint.h>


int max_array(const int *a, size_t n)
{

    size_t i;
    int max=0;

    if(a == NULL || n == 0)
        return -1;

    max = a[0];
    for(i=1; i<n; i++) {
        if ((int)a[i] > max)
            max = (int)a[i];
    }
    return max;
}

void reverse_string(char *s)
{
    size_t i;
    char tmp;
    if(NULL == s)
        return;
    size_t len = strlen(s);
    for(i=0; i < len/2; i++) {
        tmp=s[i];
        s[i]=s[len-i-1];
        s[len-i-1] = tmp;
    }
}

int count_bits(uint32_t x)
{
    int bits=0;
    while(x>0) {
        bits += x&0x1;
        x = x >> 1;
    }
    return bits;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t remove_duplicates(int *a, size_t n) {
    if (a == NULL || n == 0) return 0;
    size_t new_n = 1;
    for (size_t i = 1; i < n; i++) {
        int found = 0;
        for (size_t j = 0; j < new_n; j++) {
            if (a[i] == a[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            a[new_n++] = a[i];
        }
    }
    return new_n;
}
