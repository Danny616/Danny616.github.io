#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    static vector<int> topKFrequent(const vector<int>& nums, const int k) {
        // Step 1: Frequency Counting
        unordered_map<int, int> freq_map;
        for (int num : nums) {
            freq_map[num]++;
        }

        // Step 2: Bucket Sort
        const int n = static_cast<int>(nums.size());  // Cast size to int to avoid issues
        vector<vector<int>> buckets(n + 1);
        for (const auto& [num, freq] : freq_map) {
            buckets[freq].push_back(num);
        }

        // Step 3: Collect Top K Elements
        vector<int> result;
        for (int freq = n; freq >= 1 && static_cast<int>(result.size()) < k; --freq) {  // Ensure type consistency in comparison
            for (int num : buckets[freq]) {
                result.push_back(num);
                if (static_cast<int>(result.size()) == k) {  // Again ensure type consistency
                    break;
                }
            }
        }

        return result;
    }
};

int main() {
    // Read the input array
    cout << "Enter the array elements separated by spaces: ";
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> nums;
    int num;
    while (iss >> num) {
        nums.push_back(num);
    }

    // Read the value of k
    int k;
    cout << "Enter k: ";
    cin >> k;

    // Get the top k frequent elements
    const vector<int> result = Solution::topKFrequent(nums, k);

    // Print the result
    cout << "The top " << k << " frequent elements are: ";
    for (const int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}