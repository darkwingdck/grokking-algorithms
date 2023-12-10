int binary_search(int *nums, int nums_length, int target) {
    int low = 0;
    int high = nums_length - 1;

    while (low <= high) {
        int mid = (high + low) / 2;
        int current = nums[mid];

        if (current == target) {
            return mid;
        }

        if (nums[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}
