#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    static void dfs(const int node, const int depth, vector<int>& edges, vector<int>& state, vector<int>& dist, int& ans) {
        state[node] = 1; // Mark as visiting
        dist[node] = depth;
        const int next_node = edges[node];
        if (next_node != -1) {
            if (state[next_node] == 0) {
                dfs(next_node, depth + 1, edges, state, dist, ans);
            } else if (state[next_node] == 1) {
                // Cycle detected
                const int cycle_length = depth - dist[next_node] + 1;
                ans = max(ans, cycle_length);
            }
            // If state[next_node] == 2, it's already visited, do nothing
        }
        state[node] = 2; // Mark as visited
    }

    static int longestCycle(vector<int>& edges) {
        const int n = edges.size();
        vector<int> state(n, 0); // 0: unvisited, 1: visiting, 2: visited
        vector<int> dist(n, -1); // Depth at which each node is visited
        int ans = -1;

        for (int i = 0; i < n; ++i) {
            if (state[i] == 0) {
                dfs(i, 0, edges, state, dist, ans);
            }
        }
        return ans;
    }
};

// Example usage:
int main() {
    vector<int> edges1 = {3, 3, 4, 2, 3};
    vector<int> edges2 = {2, -1, 3, 1};

    cout << Solution::longestCycle(edges1) << endl;
    cout << Solution::longestCycle(edges2) << endl;

    return 0;
}
