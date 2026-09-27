#include "block3.h"

bool is_power_of_two(uint32_t x) {
    unsigned i;
    uint32_t sum=0;
    if(x==0)
        return false;
    for(i=0; i<32;i++) {
        sum+= x&0x1;
        x = x>>1;
    }

    if(sum<2)
        return true;

    return false;
}




unsigned count_set_bits(uint32_t x)
{
    unsigned i;
    uint32_t sum=0;
    for(i=0; i<32;i++) {
        sum+= x&0x1;
        x = x>>1;
    }
    return sum;
}

uint32_t reverse_bits(uint32_t x)
{
    unsigned i;
    uint32_t ret=0;
    for(i=0; i<32;i++) {
        ret |= ((x>>(31-i)) & 0x1 )<<i;
    }
    return ret;
}


uint32_t extract_bits(uint32_t x,
                      unsigned start,
                      unsigned width)
{
    unsigned i;
    uint32_t extract =0;

    if (start > 31 || width < 1)
        return 0;
    if(width >= 32 - start)
        width = 32 - start;
    x = x >> start;
    for(i=0; i<width; i++) {
        extract |= x & (UINT32_C(1) << i);
    }
    return extract;
}


uint32_t set_bit_field(uint32_t x,
                       unsigned start,
                       unsigned width,
                       uint32_t value)
{
    if (start > 31 || width < 1)
        return 0;
    if(width >= 32 - start)
        width = 32 - start;
    
    uint32_t mask = UINT32_MAX >> (32 - width);

    value = value & mask;
    x = x & ~(mask<<start);
    x |= value << start;
    return x;
}
