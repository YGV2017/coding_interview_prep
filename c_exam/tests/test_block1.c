#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "block1.h"

void test_remove_duplicates() {
    printf("Testing remove_duplicates...\n");
    int arr1[] = {1, 2, 2, 3, 4, 4, 5};
    size_t n1 = 7;
    size_t new_n1 = remove_duplicates(arr1, n1);
    assert(new_n1 == 5);
    assert(arr1[0] == 1);
    assert(arr1[1] == 2);
    assert(arr1[2] == 3);
    assert(arr1[3] == 4);
    assert(arr1[4] == 5);

    int arr2[] = {1, 1, 1, 1};
    size_t new_n2 = remove_duplicates(arr2, 4);
    assert(new_n2 == 1);
    assert(arr2[0] == 1);

    int arr3[] = {1, 2, 3};
    size_t new_n3 = remove_duplicates(arr3, 3);
    assert(new_n3 == 3);

    assert(remove_duplicates(NULL, 10) == 0);
    printf("remove_duplicates passed!\n");
}

void test_max_array() {
    printf("Testing max_array...\n");
    int arr1[] = {1, 5, 3, 9, 2};
    assert(max_array(arr1, 5) == 9);

    int arr2[] = {-10, -5, -20, -2};
    assert(max_array(arr2, 4) == -2);

    int arr3[] = {100};
    assert(max_array(arr3, 1) == 100);

    assert(max_array(NULL, 0) == -1);
    assert(max_array(arr1, 0) == -1);
    printf("max_array passed!\n");
}

void test_reverse_string() {
    printf("Testing reverse_string...\n");
    char s1[] = "hello";
    reverse_string(s1);
    assert(strcmp(s1, "olleh") == 0);

    char s2[] = "abcd";
    reverse_string(s2);
    assert(strcmp(s2, "dcba") == 0);

    char s3[] = "";
    reverse_string(s3);
    assert(strcmp(s3, "") == 0);

    char s4[] = "a";
    reverse_string(s4);
    assert(strcmp(s4, "a") == 0);

    reverse_string(NULL); // Should not crash
    printf("reverse_string passed!\n");
}

void test_count_bits() {
    printf("Testing count_bits...\n");
    assert(count_bits(0) == 0);
    assert(count_bits(1) == 1);
    assert(count_bits(7) == 3); // 111
    assert(count_bits(0xFFFFFFFF) == 32);
    assert(count_bits(0x10101010) == 4);
    printf("count_bits passed!\n");
}

void test_swap() {
    printf("Testing swap...\n");
    int x = 10, y = 20;
    swap(&x, &y);
    assert(x == 20);
    assert(y == 10);

    int a = -5, b = 0;
    swap(&a, &b);
    assert(a == 0);
    assert(b == -5);
    printf("swap passed!\n");
}

int main() {
    test_max_array();
    test_reverse_string();
    test_count_bits();
    test_swap();
    test_remove_duplicates();

    printf("\nAll tests passed successfully!\n");
    return 0;
}


