#include <iostream>
using namespace std;

class Solution {
public:
    static double myPow(double x, const int n) {
        // Handle the case where n is negative
        long long power = n; // Use long long to avoid overflow for INT_MIN
        if (power < 0) {
            x = 1 / x;
            power = -power;
        }

        double result = 1.0;
        while (power > 0) {
            // If the current power is odd, multiply the result by x
            if (power % 2 == 1) {
                result *= x;
            }
            // Square x and halve the power
            x *= x;
            power /= 2;
        }

        return result;
    }
};

int main() {

    cout << Solution::myPow(2.00000, 10) << endl; // Output: 1024.00000
    cout << Solution::myPow(2.10000, 3) << endl;  // Output: 9.26100
    cout << Solution::myPow(2.00000, -2) << endl; // Output: 0.25000

    return 0;
}
