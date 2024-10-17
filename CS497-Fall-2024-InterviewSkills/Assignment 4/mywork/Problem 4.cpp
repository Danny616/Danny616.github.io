#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int shortestSubarray(const vector<int>& nums, const int k) {
    const size_t n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    deque<size_t> dq;
    size_t result = n + 1;

    for (size_t i = 0; i <= n; ++i) {
        // Check if we can form a valid subarray with sum >= k
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            result = min(result, i - dq.front());
            dq.pop_front();
        }

        // Maintain increasing order in deque
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }

        // Add current index to deque
        dq.push_back(i);
    }

    // If the result was updated, return it; otherwise, return -1 (no such subarray found)
    return result == n + 1 ? -1 : static_cast<int>(result);
}

int main() {
    const vector<int> nums1 = {1};
    constexpr int k1 = 1;
    cout << "Example 1: " << shortestSubarray(nums1, k1) << endl;  // Output: 1

    const vector<int> nums2 = {1, 2};
    constexpr int k2 = 4;
    cout << "Example 2: " << shortestSubarray(nums2, k2) << endl;  // Output: -1

    const vector<int> nums3 = {2, -1, 2};
    constexpr int k3 = 3;
    cout << "Example 3: " << shortestSubarray(nums3, k3) << endl;  // Output: 3

    return 0;
}