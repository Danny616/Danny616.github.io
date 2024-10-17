#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    static vector<int> findClosestElements(vector<int>& arr, const int k, const int x) {
        const int n = arr.size();
        int left = 0;
        int right = n - k;  // Possible starting index of k elements

        // Perform binary search to find the starting index
        while (left < right) {
            const int mid = left + (right - left) / 2;
            // Compare distances
            if (x - arr[mid] > arr[mid + k] - x) {
                // Move to the right half
                left = mid + 1;
            } else {
                // Stay in the left half
                right = mid;
            }
        }

        // Extract the k closest elements
        return {arr.begin() + left, arr.begin() + left + k};
    }
};

int main() {
    // Read the input array
    cout << "Enter the sorted array elements separated by spaces: ";
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> arr;
    int num;
    while (iss >> num) {
        arr.push_back(num);
    }

    // Read the value of k and x
    int k, x;
    cout << "Enter k: ";
    cin >> k;
    cout << "Enter x: ";
    cin >> x;

    // Get the k closest elements to x
    const vector<int> result = Solution::findClosestElements(arr, k, x);

    // Print the result
    cout << "The " << k << " closest elements to " << x << " are: ";
    for (const int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}