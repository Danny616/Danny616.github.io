#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    static int shortestPathLength(const vector<vector<int>>& graph) {
        const size_t n = graph.size();
        if (n == 1) return 0;
        const int ending_mask = (1 << n) - 1;
        queue<pair<int, int>> q; // (current_node, visited_mask)
        vector<vector<bool>> visited(n, vector<bool>(1 << n, false));

        // Initialize the queue with all starting nodes
        for (size_t i = 0; i < n; ++i) {
            int mask = 1 << i;
            q.emplace(i, mask);
            visited[i][mask] = true;
        }

        int steps = 0;

        while (!q.empty()) {
            size_t size = q.size();
            while (size--) {
                auto [curr_node, curr_mask] = q.front(); q.pop();
                // Check if all nodes are visited
                if (curr_mask == ending_mask) {
                    return steps;
                }
                // Visit all the neighbors
                for (int neighbor : graph[curr_node]) {
                    int next_mask = curr_mask | 1 << neighbor;
                    if (!visited[neighbor][next_mask]) {
                        visited[neighbor][next_mask] = true;
                        q.emplace(neighbor, next_mask);
                    }
                }
            }
            ++steps;
        }
        return -1; // Should never reach here since the graph is connected
    }
};

// Example usage:
int main() {
    const vector<vector<int>> graph1 = {{1,2,3},{0},{0},{0}};
    cout << "Shortest path length (Example 1): " << Solution::shortestPathLength(graph1) << endl;

    const vector<vector<int>> graph2 = {{1},{0,2,4},{1,3,4},{2},{1,2}};
    cout << "Shortest path length (Example 2): " << Solution::shortestPathLength(graph2) << endl;

    return 0;
}