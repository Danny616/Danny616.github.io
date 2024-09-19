#include <iostream>
#include <string>
#include <vector>

using namespace std;

string removeDuplicateLetters(const string& s) {
    vector<int> count(26, 0); // To count the occurrences of each character
    vector<bool> in_stack(26, false); // To track characters in stack
    string result;

    // Count occurrences of each character
    for (const char c : s) {
        count[c - 'a']++;
    }

    for (const char c : s) {
        const int index = c - 'a';
        count[index]--;

        if (in_stack[index]) continue;

        // Remove characters that are greater than current and can appear later
        while (!result.empty() && result.back() > c && count[result.back() - 'a'] > 0) {
            in_stack[result.back() - 'a'] = false;
            result.pop_back();
        }

        result += c;
        in_stack[index] = true;
    }

    return result;
}

int main() {
    string s1 = "bcabc";
    cout << "Remove duplicate letters (\"bcabc\"): " << removeDuplicateLetters(s1) << endl;  // Output: "abc"

    string s2 = "cbacdcbc";
    cout << "Remove duplicate letters (\"cbacdcbc\"): " << removeDuplicateLetters(s2) << endl;  // Output: "acdb"

    return 0;
}