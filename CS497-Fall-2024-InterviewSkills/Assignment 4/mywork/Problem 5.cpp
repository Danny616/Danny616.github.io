#include <vector>
#include <iostream>
using namespace std;

vector<int> kthSmallestPrimeFraction(vector<int>& arr, const int k) {
    using size_type = std::vector<int>::size_type;
    const size_type n = arr.size();

    double low = 0.0, high = 1.0;

    // Perform binary search to find the kth smallest fraction
    while (true) {
        const double mid = (low + high) / 2.0;

        size_type total = 0;
        vector<int> best = {0, 1};
        size_type i = 0;

        // Count the number of fractions less than mid
        for (size_type j = 1; j < n; ++j) {
            while (i < j && arr[i] < mid * arr[j]) ++i;
            total += i;

            // Update the best fraction found so far
            if (i > 0 && arr[i - 1] * best[1] > arr[j] * best[0]) {
                best = {arr[i - 1], arr[j]};
            }
        }

        // Check if we found the kth smallest fraction
        if (total == static_cast<size_type>(k)) {
            return best;
        }

        // Update the search range based on the total count
        if (total < static_cast<size_type>(k)) {
            low = mid;
        } else {
            high = mid;
        }
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 5};
    constexpr int k = 4;

    const vector<int> result = kthSmallestPrimeFraction(arr, k);

    cout << "The " << k << "th smallest fraction is: " << result[0] << "/" << result[1] << endl;

    return 0;
}