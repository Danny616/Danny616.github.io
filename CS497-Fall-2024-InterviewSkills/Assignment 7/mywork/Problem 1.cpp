#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool canFinish(const int numCourses, const vector<vector<int>>& prerequisites) {
    // Create an adjacency list for the graph
    vector<vector<int>> adj(numCourses);
    // Create an in-degree array to track incoming edges
    vector<int> inDegree(numCourses, 0);

    // Populate the adjacency list and in-degree array
    for (const auto& prerequisite : prerequisites) {
        int course = prerequisite[0];
        const int prerequisiteCourse = prerequisite[1];
        adj[prerequisiteCourse].push_back(course);
        inDegree[course]++;
    }

    // Initialize a queue for courses with no prerequisites
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Perform BFS
    int visitedCourses = 0;
    while (!q.empty()) {
        const int course = q.front();
        q.pop();
        visitedCourses++;

        for (int nextCourse : adj[course]) {
            inDegree[nextCourse]--;
            if (inDegree[nextCourse] == 0) {
                q.push(nextCourse);
            }
        }
    }

    // If we've visited all courses, return true
    return visitedCourses == numCourses;
}

int main() {
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    cout << (canFinish(numCourses1, prerequisites1) ? "true" : "false") << endl;

    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    cout << (canFinish(numCourses2, prerequisites2) ? "true" : "false") << endl;

    return 0;
}