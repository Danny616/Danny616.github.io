#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class HeapElement {
public:
    int value;
    int index;

    HeapElement(const int val, const int idx) : value(val), index(idx) {}

    // Comparator to simulate max-heap based on the values
    bool operator<(const HeapElement &other) const {
        return value < other.value;  // Max heap: larger values should come first
    }
};

vector<int> peekTopK(const vector<int>& arr, const int k) {
    vector<int> result;

    if (arr.empty() || k <= 0) {
        return result;  // Edge case: if heap is empty, or k is non-positive
    }

    priority_queue<HeapElement> pq;

    // Start with the root of the heap (index 0)
    pq.emplace(arr[0], 0);

    while (!pq.empty() && result.size() < k) {
        HeapElement current = pq.top();
        pq.pop();

        result.push_back(current.value);

        int leftChildIdx = 2 * current.index + 1;
        int rightChildIdx = 2 * current.index + 2;

        // If the left child exists, add it to the queue
        if (leftChildIdx < arr.size()) {
            pq.emplace(arr[leftChildIdx], leftChildIdx);
        }

        // If the right child exists, add it to the queue
        if (rightChildIdx < arr.size()) {
            pq.emplace(arr[rightChildIdx], rightChildIdx);
        }
    }

    return result;
}

int main() {
    const vector<int> heap = {15, 13, 12, 10, 8, 9};
    constexpr int k = 5;

    const vector<int> result = peekTopK(heap, k);

    cout << "Top " << k << " elements: ";
    for (const int num : result) {
        cout << num << " ";
    }

    return 0;
}