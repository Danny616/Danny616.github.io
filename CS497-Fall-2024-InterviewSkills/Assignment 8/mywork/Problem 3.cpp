#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static int coinChange(const vector<int>& coins, const int amount) {
        // Edge case: if amount is 0, no coins are needed.
        if (amount == 0) return 0;

        // Initialize DP array
        // Use amount + 1 as a sentinel for "impossible"
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (const int c : coins) {
            for (int i = c; i <= amount; ++i) {
                if (dp[i - c] != amount + 1) {
                    dp[i] = min(dp[i], dp[i - c] + 1);
                }
            }
        }

        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }
};

int main() {

    {
        vector<int> coins = {1,2,5};
        int amount = 11;
        cout << Solution::coinChange(coins, amount) << endl; // Expected 3 (5 + 5 + 1)
    }

    {
        vector<int> coins = {2};
        int amount = 3;
        cout << Solution::coinChange(coins, amount) << endl; // Expected -1
    }

    {
        vector<int> coins = {1};
        int amount = 0;
        cout << Solution::coinChange(coins, amount) << endl; // Expected 0
    }

    return 0;
}
