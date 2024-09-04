#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(const int x) : val(x), next(nullptr) {}
};

// Comparator for the priority queue to sort the ListNodes based on their values.
struct Compare {
    bool operator()(const ListNode* a, const ListNode* b) const {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(const vector<ListNode*>& lists) {
    // Min-heap to keep track of the smallest elements of each list.
    priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

    // Initialize the heap with the head of each list.
    for (ListNode* list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }

    // Dummy node to form the merged linked list.
    auto* dummy = new ListNode(0);
    ListNode* current = dummy;

    // While the heap is not empty, keep adding the smallest element to the merged list.
    while (!minHeap.empty()) {
        ListNode* smallest = minHeap.top();
        minHeap.pop();
        current->next = smallest; // Add the smallest node to the merged list.
        current = current->next;  // Move to the next node.

        if (smallest->next) {
            minHeap.push(smallest->next); // Push the next node of the current list into the heap.
        }
    }

    // Get the merged list's head and free the dummy node.
    ListNode* mergedHead = dummy->next;
    delete dummy; // Avoid memory leak by deleting the dummy node.

    return mergedHead;
}

// Utility function to print the linked list.
void printList(const ListNode* node) {
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    // Example 1: lists = [[1,4,5],[1,3,4],[2,6]]
    auto* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    auto* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    auto* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    const vector<ListNode*> lists = {l1, l2, l3};
    const ListNode* result = mergeKLists(lists);

    printList(result); // Output: 1 1 2 3 4 4 5 6

    // Free the allocated memory
    const ListNode* current = result;
    while (current) {
        const ListNode* next = current->next;
        delete current;
        current = next;
    }
}