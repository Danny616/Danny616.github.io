#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static vector<int> lexicalOrder(const int n) {
        vector<int> result;
        int curr = 1;

        for (int i = 0; i < n; ++i) {
            result.push_back(curr);

            if (curr * 10 <= n) {
                curr *= 10; // Move to the smallest lex child
            } else {
                while (curr % 10 == 9 || curr + 1 > n) {
                    curr /= 10; // Backtrack to find the next valid ancestor
                }
                curr += 1; // Move to the next sibling
            }
        }

        return result;
    }
};

// Example usage:
int main() {
    constexpr int n1 = 13;
    const vector<int> result1 = Solution::lexicalOrder(n1);
    cout << "Lexicographical order up to " << n1 << ": ";
    for (const int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    constexpr int n2 = 2;
    const vector<int> result2 = Solution::lexicalOrder(n2);
    cout << "Lexicographical order up to " << n2 << ": ";
    for (const int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}