#include <vector>
#include <iostream>
using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;

    explicit UnionFind(const int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Initialize each node as its own parent
        }
    }

    int find(const int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(const int x, const int y) {
        const int rootX = find(x);
        const int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

bool validPath(const int n, const vector<vector<int>>& edges, const int source, const int destination) {
    UnionFind uf(n);

    // Unite all nodes based on edges
    for (const auto& edge : edges) {
        uf.unite(edge[0], edge[1]);
    }

    // Check if source and destination are in the same connected component
    return uf.find(source) == uf.find(destination);
}

int main() {
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};

    if (validPath(3, edges1, 0, 2)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    if (validPath(6, edges2, 0, 5)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}