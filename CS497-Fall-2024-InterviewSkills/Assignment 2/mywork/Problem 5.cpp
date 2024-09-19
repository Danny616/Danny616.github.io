#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

int shortestSubarray(const vector<int>& nums, const int k) {
    const size_t n = nums.size();
    vector<long> prefix(n + 1, 0); // Prefix sum array
    for (size_t i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    deque<size_t> dq; // Deque to store indices of prefix sum
    int min_length = INT_MAX;

    for (size_t i = 0; i < n + 1; ++i) {
        // Check if the current prefix sum - the smallest prefix sum in the deque is at least k
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            min_length = min(min_length, static_cast<int>(i - dq.front()));
            dq.pop_front();
        }

        // Maintain the deque in increasing order of prefix sums
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    return min_length == INT_MAX ? -1 : min_length;
}

int main() {
    const vector<int> nums1 = {1};
    constexpr int k1 = 1;
    cout << "Shortest subarray length with sum at least " << k1 << ": " << shortestSubarray(nums1, k1) << endl;  // Output: 1

    const vector<int> nums2 = {1, 2};
    constexpr int k2 = 4;
    cout << "Shortest subarray length with sum at least " << k2 << ": " << shortestSubarray(nums2, k2) << endl;  // Output: -1

    const vector<int> nums3 = {2, -1, 2};
    constexpr int k3 = 3;
    cout << "Shortest subarray length with sum at least " << k3 << ": " << shortestSubarray(nums3, k3) << endl;  // Output: 3

    return 0;
}