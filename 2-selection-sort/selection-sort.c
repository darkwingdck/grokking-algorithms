void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int *nums, int nums_length) {
    for (int i = 0; i < nums_length; i++) {
        int minimum_index = i;
        for (int j = i + 1; j < nums_length; j++) {
            if (nums[j] < nums[minimum_index]) {
                minimum_index = j;
            }
        }
        swap(&nums[i], &nums[minimum_index]);
    }
}
