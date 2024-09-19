#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximumGap(vector<int>& nums) {
    if (nums.size() < 2) return 0;

    const int min_val = *min_element(nums.begin(), nums.end());
    const int max_val = *max_element(nums.begin(), nums.end());

    const size_t n = nums.size();
    const int bucket_size = max(1, (max_val - min_val) / static_cast<int>(n - 1));  // Minimum possible max gap
    const size_t bucket_count = (max_val - min_val) / bucket_size + 1;

    vector<pair<int, int>> buckets(bucket_count, {-1, -1});  // {min_value, max_value}

    for (int num : nums) {
        const size_t idx = (num - min_val) / bucket_size;
        if (buckets[idx].first == -1) {
            buckets[idx].first = num;
            buckets[idx].second = num;
        } else {
            buckets[idx].first = min(buckets[idx].first, num);
            buckets[idx].second = max(buckets[idx].second, num);
        }
    }

    int max_gap = 0;
    int prev_max = min_val;
    for (const auto& bucket : buckets) {
        if (bucket.first == -1) continue;
        max_gap = max(max_gap, bucket.first - prev_max);
        prev_max = bucket.second;
    }

    return max_gap;
}

int main() {
    vector<int> nums1 = {3, 6, 9, 1};
    cout << "Maximum gap: " << maximumGap(nums1) << endl;  // Output: 3

    vector<int> nums2 = {10};
    cout << "Maximum gap: " << maximumGap(nums2) << endl;  // Output: 0

    return 0;
}