#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twoSum(const vector<int>& nums, const int target) {
    unordered_map<int, int> num_map; // Maps numbers to their indices
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i]; // Find the complement of the current number
        if (num_map.find(complement) != num_map.end()) {
            // If the complement is found in the map, return the indices
            return {num_map[complement], i};
        }
        // Otherwise, add the current number and its index to the map
        num_map[nums[i]] = i;
    }
    return {}; // Should never reach here since a solution is guaranteed
}

int main() {
    const vector<int> nums1 = {2, 7, 11, 15};
    constexpr int target1 = 9;
    const vector<int> result1 = twoSum(nums1, target1);
    cout << "[" << result1[0] << ", " << result1[1] << "]" << endl; // Output: [0, 1]

    const vector<int> nums2 = {3, 2, 4};
    constexpr int target2 = 6;
    const vector<int> result2 = twoSum(nums2, target2);
    cout << "[" << result2[0] << ", " << result2[1] << "]" << endl; // Output: [1, 2]

    const vector<int> nums3 = {3, 3};
    constexpr int target3 = 6;
    const vector<int> result3 = twoSum(nums3, target3);
    cout << "[" << result3[0] << ", " << result3[1] << "]" << endl; // Output: [0, 1]

    return 0;
}