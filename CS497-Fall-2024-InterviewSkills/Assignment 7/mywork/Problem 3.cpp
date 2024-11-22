#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Union-Find (Disjoint Set Union) class
class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;

    explicit UnionFind(const int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0); // Initialize parent array
    }

    int find(const int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(const int x, const int y) {
        const int rootX = find(x);
        const int rootY = find(y);
        if (rootX == rootY) return false;

        // Union by rank
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int minCostToSupplyWater(const int n, vector<int>& wells, const vector<vector<int>>& pipes) {
    vector<vector<int>> edges;

    // Add virtual node 0 connections to the edges
    edges.reserve(wells.size());
for (int i = 0; i < wells.size(); ++i) {
        edges.push_back({0, i + 1, wells[i]}); // Virtual node 0 connected to house i+1
    }

    // Add existing pipes to the edges
    for (const auto& pipe : pipes) {
        edges.push_back(pipe);
    }

    // Sort edges by cost
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });

    // Kruskal's algorithm to find MST
    UnionFind uf(n + 1); // Include the virtual node 0
    int totalCost = 0;

    for (const auto& edge : edges) {
        const int u = edge[0], v = edge[1], cost = edge[2];
        if (uf.unite(u, v)) {
            totalCost += cost;
        }
    }

    return totalCost;
}

int main() {
    int n1 = 3;
    vector<int> wells1 = {1, 2, 2};
    vector<vector<int>> pipes1 = {{1, 2, 1}, {2, 3, 1}};
    cout << minCostToSupplyWater(n1, wells1, pipes1) << endl; // Output: 3

    return 0;
}