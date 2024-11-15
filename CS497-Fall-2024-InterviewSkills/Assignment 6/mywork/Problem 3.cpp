#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;

    explicit UnionFind(const int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(const int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(const int x, const int y) {
        const int rootX = find(x);
        const int rootY = find(y);
        if (rootX == rootY) {
            return false; // Already in the same set
        }
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

int minimumCost(const int N, vector<vector<int>>& connections) {
    // Sort connections by cost (ascending)
    sort(connections.begin(), connections.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });

    UnionFind uf(N);
    int totalCost = 0;
    int edgesUsed = 0;

    // Process edges in order of cost
    for (const auto& connection : connections) {
        const int city1 = connection[0], city2 = connection[1], cost = connection[2];
        if (uf.unite(city1, city2)) {
            totalCost += cost;
            edgesUsed++;
            // If we have connected all N-1 edges, we are done
            if (edgesUsed == N - 1) {
                return totalCost;
            }
        }
    }

    // If we didn't use enough edges to connect all cities, return -1
    return -1;
}

int main() {
    vector<vector<int>> connections1 = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    vector<vector<int>> connections2 = {{1, 2, 3}, {3, 4, 4}};

    cout << minimumCost(3, connections1) << endl; // Output: 6
    cout << minimumCost(4, connections2) << endl; // Output: -1

    return 0;
}
