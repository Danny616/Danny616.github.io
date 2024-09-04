#include <iostream>
#include <vector>
#include <climits>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is the smaller array to make binary search easier
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }

    using size_type = std::vector<int>::size_type;  // Use size_type for sizes and indices
    const size_type m = nums1.size();
    const size_type n = nums2.size();

    size_type low = 0, high = m;
    while (low <= high) {
        const size_type partition1 = (low + high) / 2;
        const size_type partition2 = (m + n + 1) / 2 - partition1;

        const int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        const int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];

        const int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        const int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // Found the correct partition
            if ((m + n) % 2 == 0) {
                return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
            } else {
                return max(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            // Move towards the left in nums1
            high = partition1 - 1;
        } else {
            // Move towards the right in nums1
            low = partition1 + 1;
        }
    }

    throw invalid_argument("Input arrays are not sorted");
}

int main() {
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Median is: " << findMedianSortedArrays(nums1, nums2) << endl;

    vector<int> nums1_2 = {1, 2};
    vector<int> nums2_2 = {3, 4};
    cout << "Median is: " << findMedianSortedArrays(nums1_2, nums2_2) << endl;

    return 0;
}