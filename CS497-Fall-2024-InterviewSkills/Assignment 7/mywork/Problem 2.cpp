#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int networkDelayTime(const vector<vector<int>>& times, const int n, int k) {
    // Build the adjacency list
    vector<vector<pair<int, int>>> graph(n + 1);
    for (const auto& time : times) {
        const int u = time[0];
        int v = time[1];
        int w = time[2];
        graph[u].emplace_back(v, w);
    }

    // Min-heap priority queue to store (time, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(n + 1, INT_MAX); // Distance to each node
    dist[k] = 0;
    pq.emplace(0, k); // (time, source)

    // Dijkstra's algorithm
    while (!pq.empty()) {
        auto [time, node] = pq.top();
        pq.pop();

        if (time > dist[node]) continue;

        for (const auto& [neighbor, weight] : graph[node]) {
            int newTime = time + weight;
            if (newTime < dist[neighbor]) {
                dist[neighbor] = newTime;
                pq.emplace(newTime, neighbor);
            }
        }
    }

    // Find the maximum time it takes to reach any node
    int maxTime = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INT_MAX) return -1; // If a node is unreachable
        maxTime = max(maxTime, dist[i]);
    }

    return maxTime;
}

int main() {
    vector<vector<int>> times1 = {{1, 2, 1}};
    int n1 = 2, k1 = 1;
    cout << networkDelayTime(times1, n1, k1) << endl; // Output: 1

    vector<vector<int>> times2 = {{1, 2, 1}};
    int n2 = 2, k2 = 2;
    cout << networkDelayTime(times2, n2, k2) << endl; // Output: -1

    vector<vector<int>> times3 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n3 = 4, k3 = 2;
    cout << networkDelayTime(times3, n3, k3) << endl; // Output: 2

    return 0;
}