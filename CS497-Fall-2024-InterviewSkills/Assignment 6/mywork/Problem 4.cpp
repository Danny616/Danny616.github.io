#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    static void dfs(const int node, vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& result) {
        path.push_back(node); // Add the current node to the path

        if (node == graph.size() - 1) {
            // If we reach the target node, save the current path
            result.push_back(path);
        } else {
            // Continue DFS for each neighbor
            for (const int neighbor : graph[node]) {
                dfs(neighbor, graph, path, result);
            }
        }

        // Backtrack: remove the current node from the path
        path.pop_back();
    }

    static vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result; // To store all paths
        vector<int> path;           // To track the current path
        dfs(0, graph, path, result);
        return result;
    }
};

int main() {
    vector<vector<int>> graph1 = {{1, 2}, {3}, {3}, {}};
    vector<vector<int>> graph2 = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};

    const vector<vector<int>> result1 = Solution::allPathsSourceTarget(graph1);
    const vector<vector<int>> result2 = Solution::allPathsSourceTarget(graph2);

    for (const auto& path : result1) {
        for (const int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (const auto& path : result2) {
        for (const int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}