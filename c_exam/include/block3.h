#ifndef BIT_EXERCISES_H
#define BIT_EXERCISES_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Return true if x is a power of two.
 *
 * Examples:
 *   1  -> true
 *   2  -> true
 *   8  -> true
 *   10 -> false
 *   0  -> false
 */
bool is_power_of_two(uint32_t x);


/*
 * Count how many bits are set to 1 in x.
 *
 * Examples:
 *   0x00000000 -> 0
 *   0x00000001 -> 1
 *   0x0000000F -> 4
 *   0xFFFFFFFF -> 32
 */
unsigned count_set_bits(uint32_t x);


/*
 * Reverse all 32 bits in x.
 *
 * Example:
 *   bit 0 becomes bit 31
 *   bit 1 becomes bit 30
 *   ...
 *
 * Example:
 *   0x00000001 -> 0x80000000
 */
uint32_t reverse_bits(uint32_t x);


/*
 * Extract a consecutive bit field from x.
 *
 * start:
 *   index of the least-significant bit of the field.
 *
 * width:
 *   number of bits to extract.
 *
 * The extracted field should be returned right-aligned.
 *
 * Example:
 *   x     = 0b11010110
 *   start = 2
 *   width = 3
 *
 * Extract bits 2,3,4 -> 0b101
 *
 * Assume:
 *   start < 32
 *   width >= 1
 *   start + width <= 32
 */
uint32_t extract_bits(uint32_t x,
                      unsigned start,
                      unsigned width);


/*
 * Replace a consecutive bit field inside x.
 *
 * All bits outside the requested field must remain unchanged.
 *
 * start:
 *   index of the least-significant bit of the field.
 *
 * width:
 *   number of bits in the field.
 *
 * value:
 *   new value to insert into the field.
 *   Only the lowest 'width' bits of value should be used.
 *
 * Example:
 *
 *   x     = 0b11110000
 *   start = 2
 *   width = 3
 *   value = 0b001
 *
 * Replace bits 2..4 while preserving all other bits.
 *
 * Assume:
 *   start < 32
 *   width >= 1
 *   start + width <= 32
 */
uint32_t set_bit_field(uint32_t x,
                       unsigned start,
                       unsigned width,
                       uint32_t value);

#endif