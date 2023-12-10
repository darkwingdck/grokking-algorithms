#include "binary-search.h"

#include <assert.h>
#include <stdio.h>

int test_binary_search() {
    int test_numbers_1[5] = {1, 2, 3, 4, 5};
    int test_numbers_2[5] = {1, 2, 3, 4, 5};
    int test_numbers_3[5] = {1, 2, 3, 4, 5};
    int test_numbers_4[0] = {};
    int test_numbers_5[1] = {1};
    assert(binary_search(test_numbers_1, 5, 2) == 1);
    assert(binary_search(test_numbers_2, 5, 1) == 0);
    assert(binary_search(test_numbers_3, 5, 6) == -1);
    assert(binary_search(test_numbers_4, 0, 5) == -1);
    assert(binary_search(test_numbers_5, 1, 1) == 0);
    printf("%s\n", "5/5 tests passed!");
    return 0;
}

int main() {
    test_binary_search();
    return 0;
}
