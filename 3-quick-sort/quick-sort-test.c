#include "quick-sort.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

bool array_is_equal(int *arr1, int *arr2, size_t arr1_size, size_t arr2_size) {
    if (arr1_size != arr1_size) {
        return false;
    }
    for (size_t i = 0; i < arr1_size; i++) {
        if (arr1[i] != arr2[i]) {
            printf("%d ", arr1[i]);
            printf("%d ", arr2[i]);
            return false;
        }
    }
    return true;
}

int test_quick_sort() {
    int nums_1[6] = {5, 3, 1, 2, 4, -123};
    int nums_1_sorted[6] = {-123, 1, 2, 3, 4, 5};
    quick_sort(nums_1, 0, 5);
    assert(array_is_equal(nums_1, nums_1_sorted, 6, 6) == true);

    int nums_2[5] = {1, 2, 3, 4, 0};
    int nums_2_sorted[5] = {0, 1, 2, 3, 4};
    quick_sort(nums_2, 0, 4);
    assert(array_is_equal(nums_2, nums_2_sorted, 5, 5) == true);

    int nums_3[1] = {4};
    int nums_3_sorted[1] = {4};
    quick_sort(nums_3, 0, 0);
    assert(array_is_equal(nums_3, nums_3_sorted, 1, 1) == true);

    int nums_4[] = {};
    int nums_4_sorted[] = {};
    quick_sort(nums_4, 0, -1);
    assert(array_is_equal(nums_4, nums_4_sorted, 0, 0) == true);

    int nums_5[6] = {10, 123, 23, -12, 0, 4643};
    int nums_5_sorted[6] = {-12, 0, 10, 23, 123, 4643};
    quick_sort(nums_5, 0, 5);
    assert(array_is_equal(nums_5, nums_5_sorted, 6, 6) == true);

    printf("%s\n", "5/5 tests passed!");

    return 0;
}

int main() {
    test_quick_sort();
    return 0;
}
