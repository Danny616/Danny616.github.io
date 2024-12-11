#include <iostream>

using namespace std;

class Solution {
public:
    static int divide(int dividend, int divisor) {
        // Handle overflow case
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine the sign of the result
        bool negative = ( (dividend < 0) ^ (divisor < 0) );

        // Convert both dividend and divisor to negative
        // This avoids overflow issues when dealing with INT_MIN
        long long dvd = dividend;
        long long dvs = divisor;
        if (dvd > 0) dvd = -dvd;
        if (dvs > 0) dvs = -dvs;

        int result = 0;

        while (dvd <= dvs) {
            long long temp = dvs;
            int count = 1;

            // Try to double the divisor as long as it doesn't surpass dividend
            // and it doesn't overflow.
            while ((temp << 1) >= dvd && (temp << 1) < 0) {
                temp <<= 1;
                count <<= 1;
            }

            // Subtract the biggest doubled divisor from dividend
            dvd -= temp;
            // Add the count to the result
            result += count;
        }

        return negative ? -result : result;
    }
};

// Example usage:
int main() {
    cout << Solution::divide(10, 3) << endl;    // Expected output: 3
    cout << Solution::divide(7, -3) << endl;    // Expected output: -2
    cout << Solution::divide(-2147483648, -1) << endl; // Expected output: 2147483647 (INT_MAX)
    return 0;
}