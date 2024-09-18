#include <iostream>
#include <vector>

using namespace std;

int majorityElement(const vector<int>& nums) {
    int count = 0;
    int candidate = 0;

    // Phase 1: Find a candidate
    for (const int num : nums) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }

    // Phase 2: Verify the candidate
    count = 0;
    for (const int num : nums) {
        if (num == candidate) {
            count++;
        }
    }

    // As per the problem statement, we are guaranteed a majority element exists
    return candidate;
}

int main() {
    // Example 1
    const vector<int> nums1 = {3, 2, 3};
    cout << "Majority element in [3, 2, 3] is: " << majorityElement(nums1) << endl;

    // Example 2
    const vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    cout << "Majority element in [2, 2, 1, 1, 1, 2, 2] is: " << majorityElement(nums2) << endl;

    return 0;
}