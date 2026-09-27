#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "block3.h"

void test_is_power_of_two() {
    printf("Testing is_power_of_two...\n");
    assert(is_power_of_two(1) == true);
    assert(is_power_of_two(2) == true);
    assert(is_power_of_two(4) == true);
    assert(is_power_of_two(8) == true);
    assert(is_power_of_two(1024) == true);
    assert(is_power_of_two(0) == false);
    assert(is_power_of_two(3) == false);
    assert(is_power_of_two(7) == false);
    assert(is_power_of_two(10) == false);
    assert(is_power_of_two(0xFFFFFFFF) == false);
    printf("is_power_of_two tests passed!\n");
}

void test_count_set_bits() {
    printf("Testing count_set_bits...\n");
    assert(count_set_bits(0x00000000) == 0);
    assert(count_set_bits(0x00000001) == 1);
    assert(count_set_bits(0x0000000F) == 4);
    assert(count_set_bits(0xFFFFFFFF) == 32);
    assert(count_set_bits(0x10101010) == 4);
    assert(count_set_bits(0xAAAAAAAA) == 16);
    assert(count_set_bits(0x55555555) == 16);
    printf("count_set_bits tests passed!\n");
}

void test_reverse_bits() {
    printf("Testing reverse_bits...\n");
    assert(reverse_bits(0x00000001) == 0x80000000);
    assert(reverse_bits(0x80000000) == 0x00000001);
    assert(reverse_bits(0x00000000) == 0x00000000);
    assert(reverse_bits(0xFFFFFFFF) == 0xFFFFFFFF);
    // 0x12345678 = 0001 0010 0011 0100 0101 0110 0111 1000
    // Reversed   = 0001 1110 0110 1010 0010 1100 0100 1000 = 0x1E6A2C48
    assert(reverse_bits(0x12345678) == 0x1E6A2C48);
    printf("reverse_bits tests passed!\n");
}

void test_extract_bits() {
    printf("Testing extract_bits...\n");
    // Example from header: x = 0b11010110 (0xD6), start = 2, width = 3 -> 0b101 (5)
    assert(extract_bits(UINT32_MAX, 0, 32) == UINT32_MAX);
    assert(extract_bits(UINT32_C(0x80000000), 31, 1) == 1);
    assert(extract_bits(0xD6, 2, 3) == 5);
    assert(extract_bits(0xFF, 0, 8) == 0xFF);
    assert(extract_bits(0xFF, 0, 4) == 0x0F);
    assert(extract_bits(0xFF, 4, 4) == 0x0F);
    assert(extract_bits(0xAAAAAAAA, 0, 1) == 0);
    assert(extract_bits(0xAAAAAAAA, 1, 1) == 1);
    printf("extract_bits tests passed!\n");
}

void test_set_bit_field() {
    printf("Testing set_bit_field...\n");
    // Example from header:
    // x     = 0b11110000 (0xF0)
    // start = 2
    // width = 3
    // value = 0b001 (1)
    // Bits 2,3,4 are 0,0,1 in 0xF0 (0b11110000)
    // We want to replace them with 001.
    // Result should be 0b11100100 (0xE4)
    assert(set_bit_field(0xF0, 2, 3, 1) == 0xE4);
    
    // Test full replace
    assert(set_bit_field(0x00000000, 0, 32, 0xFFFFFFFF) == 0xFFFFFFFF);
    
    assert(set_bit_field(0, 31, 1, 1) == UINT32_C(0x80000000));
    assert(set_bit_field(UINT32_MAX, 31, 1, 0) == UINT32_C(0x7fffffff));

    // Test no change (replace with same value)
    assert(set_bit_field(0x12345678, 4, 4, 0x7) == 0x12345678);
    
    printf("set_bit_field tests passed!\n");
}

int main() {
    printf("Starting tests for block3.c\n");
    
    test_count_set_bits();
    test_reverse_bits();
    test_is_power_of_two();
    test_extract_bits();
    test_set_bit_field();

    printf("All block3 tests passed!\n");
    return 0;
}
