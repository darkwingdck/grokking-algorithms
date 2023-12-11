void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int nums[], int low, int high) {
    const int pivot = nums[high];
    int i = low;
    for (int j = low; j <= high; j++) {
        if (nums[j] <= pivot) {
            swap(&nums[i], &nums[j]);
            i++;
        }
    }
    return i - 1;
}

void quick_sort(int nums[], int low, int high) {
    if (low < high) {
        int pivot = partition(nums, low, high);
        quick_sort(nums, low, pivot - 1);
        quick_sort(nums, pivot + 1, high);
    }
}
