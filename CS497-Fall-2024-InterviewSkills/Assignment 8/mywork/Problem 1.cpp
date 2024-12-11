#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    static vector<int> findOrder(const int numCourses, const vector<vector<int>>& prerequisites) {
        // Create an adjacency list to represent the graph
        vector<vector<int>> graph(numCourses);

        // in-degree array
        vector<int> inDegree(numCourses, 0);

        // Build the graph and fill in-degree array
        for (auto &pre : prerequisites) {
            int course = pre[0];
            const int prereq = pre[1];
            graph[prereq].push_back(course);
            inDegree[course]++;
        }

        // Queue for courses with no prerequisites
        queue<int> zeroDegree;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                zeroDegree.push(i);
            }
        }

        // Topological sort
        vector<int> courseOrder;
        while (!zeroDegree.empty()) {
            int curr = zeroDegree.front();
            zeroDegree.pop();
            courseOrder.push_back(curr);

            // Decrement the in-degree of neighbors
            for (int nextCourse : graph[curr]) {
                inDegree[nextCourse]--;
                if (inDegree[nextCourse] == 0) {
                    zeroDegree.push(nextCourse);
                }
            }
        }

        // If we were able to include all courses, return the order
        if (static_cast<int>(courseOrder.size()) == numCourses) {
            return courseOrder;
        }
        return {};
    }
};

// Example usage:
int main() {
    {
        int numCourses = 2;
        vector<vector<int>> prerequisites = {{1,0}};
        const vector<int> order = Solution::findOrder(numCourses, prerequisites);
        for (const int c: order) cout << c << " ";
        cout << endl; // Expected Output: 0 1
    }

    {
        int numCourses = 4;
        vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
        const vector<int> order = Solution::findOrder(numCourses, prerequisites);
        for (const int c: order) cout << c << " ";
        cout << endl; // One possible valid output: 0 2 1 3 or 0 1 2 3
    }

    {
        int numCourses = 1;
        vector<vector<int>> prerequisites = {};
        const vector<int> order = Solution::findOrder(numCourses, prerequisites);
        for (const int c: order) cout << c << " ";
        cout << endl; // Expected Output: 0
    }

    return 0;
}