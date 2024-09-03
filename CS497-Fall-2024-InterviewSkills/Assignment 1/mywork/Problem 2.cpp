#include <iostream>
#include <vector>

using namespace std;

// Helper function to find the left boundary of the target
size_t findLeftBoundary(const vector<int>& nums, const int target) {
    size_t left = 0;
    size_t right = nums.size(); // Note: using nums.size() instead of nums.size() - 1 for bounds safety
    size_t result = nums.size(); // Use nums.size() as the 'not found' indicator

    while (left < right) {
        const size_t mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;  // move left to continue searching for the first occurrence
        }
    }

    if (left < nums.size() && nums[left] == target) {
        result = left;
    }

    return result;
}

// Helper function to find the right boundary of the target
size_t findRightBoundary(const vector<int>& nums, const int target) {
    size_t left = 0;
    size_t right = nums.size();
    size_t result = nums.size(); // Use nums.size() as the 'not found' indicator

    while (left < right) {
        const size_t mid = left + (right - left) / 2;
        if (nums[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left > 0 && nums[left - 1] == target) {
        result = left - 1;
    }

    return result;
}

// Main function to find the starting and ending positions of the target
vector<int> searchRange(const vector<int>& nums, const int target) {
    const size_t leftIndex = findLeftBoundary(nums, target);
    const size_t rightIndex = findRightBoundary(nums, target);

    // If the target is not found, both indices will be nums.size()
    if (leftIndex == nums.size() || rightIndex == nums.size()) {
        return {-1, -1};
    }

    return {static_cast<int>(leftIndex), static_cast<int>(rightIndex)};
}

int main() {
    const vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    constexpr int target1 = 8;
    const vector<int> result1 = searchRange(nums1, target1);
    cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << endl;

    const vector<int> nums2 = {5, 7, 7, 8, 8, 10};
    constexpr int target2 = 6;
    const vector<int> result2 = searchRange(nums2, target2);
    cout << "Output: [" << result2[0] << ", " << result2[1] << "]" << endl;

    const vector<int> nums3 = {};
    constexpr int target3 = 0;
    const vector<int> result3 = searchRange(nums3, target3);
    cout << "Output: [" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}