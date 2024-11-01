#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    static vector<string> removeInvalidParentheses(const string& s) {
        vector<string> res;
        unordered_set<string> visited;
        queue<string> q;
        bool found = false;

        q.push(s);
        visited.insert(s);

        while (!q.empty()) {
            auto size = q.size();
            unordered_set<string> levelVisited; // To prevent duplicates at the same level
            for (decltype(size) i = 0; i < size; ++i) {
                string cur = q.front(); q.pop();

                if (isValid(cur)) {
                    res.push_back(cur);
                    found = true;
                }

                if (found) continue; // Skip generating new states if valid expressions are found

                for (size_t j = 0; j < cur.length(); ++j) {
                    if (cur[j] != '(' && cur[j] != ')') continue; // Skip letters
                    string next = cur.substr(0, j) + cur.substr(j + 1);
                    if (visited.find(next) == visited.end() && levelVisited.find(next) == levelVisited.end()) {
                        q.push(next);
                        levelVisited.insert(next);
                    }
                }
            }
            visited.insert(levelVisited.begin(), levelVisited.end());
            if (found) break;
        }

        return res;
    }

private:
    static bool isValid(const string& s) {
        int count = 0;
        for (const char& c : s) {
            if (c == '(') count++;
            else if (c == ')') {
                count--;
                if (count < 0) return false; // Early return if count is negative
            }
        }
        return count == 0;
    }
};

// Example usage:
int main() {
    const string s = "()())()";
    const vector<string> result = Solution::removeInvalidParentheses(s);
    for (const string& str : result) {
        cout << "\"" << str << "\" ";
    }
    cout << endl;
    return 0;
}