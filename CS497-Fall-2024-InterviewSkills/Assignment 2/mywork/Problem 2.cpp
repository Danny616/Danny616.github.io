#include <iostream>
#include <vector>

using namespace std;

// Functions for Kth Largest Element
int partition(vector<int>& nums, const int left, const int right) {
    const int pivot = nums[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (nums[j] > pivot) {
            swap(nums[i], nums[j]);
            ++i;
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

int quickSelect(vector<int>& nums, const int left, const int right, const int k) {
    if (left == right) {
        return nums[left];
    }

    const int pivotIndex = partition(nums, left, right);
    if (pivotIndex == k) {
        return nums[pivotIndex];
    } else if (pivotIndex < k) {
        return quickSelect(nums, pivotIndex + 1, right, k);
    } else {
        return quickSelect(nums, left, pivotIndex - 1, k);
    }
}

int findKthLargest(vector<int>& nums, const int k) {
    const size_t n = nums.size();  // Use size_t for vector size
    return quickSelect(nums, 0, static_cast<int>(n) - 1, k - 1);
}

int main() {
    // Testing Kth Largest Element
    vector<int> nums3 = {3, 2, 1, 5, 6, 4};
    constexpr int k1 = 2;
    cout << "The " << k1 << "th largest element in [3, 2, 1, 5, 6, 4] is: "
              << findKthLargest(nums3, k1) << endl;

    vector<int> nums4 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    constexpr int k2 = 4;
    cout << "The " << k2 << "th largest element in [3, 2, 3, 1, 2, 4, 5, 5, 6] is: "
              << findKthLargest(nums4, k2) << endl;

    return 0;
}