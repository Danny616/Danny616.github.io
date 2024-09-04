#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(const int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    static ListNode* removeNthFromEnd(ListNode* head, const int n) {
        // Create a dummy node that points to the head of the list
        auto* dummy = new ListNode(0);
        dummy->next = head;

        // Initialize two pointers, fast and slow
        const ListNode* fast = dummy;
        ListNode* slow = dummy;

        // Move fast pointer n+1 steps ahead to maintain the gap of n nodes
        for (int i = 0; i <= n; ++i) {
            if (fast == nullptr) {
                // If fast becomes nullptr, n is greater than the length of the list
                delete dummy;  // Clean up to prevent memory leaks
                return head;
            }
            fast = fast->next;
        }

        // Move both pointers until fast reaches the end
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // Ensure slow->next is not nullptr before accessing slow->next->next
        if (slow->next != nullptr) {
            const ListNode* nodeToRemove = slow->next;
            slow->next = slow->next->next;  // Remove the nth node from the end
            delete nodeToRemove;            // Free memory of the removed node
        }

        // Return the head of the modified list
        ListNode* newHead = dummy->next;
        delete dummy;  // Clean up the dummy node
        return newHead;
    }
};

// Helper function to print the linked list
void printList(const ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Helper function to delete the entire linked list to prevent memory leaks
void deleteList(const ListNode* head) {
    while (head != nullptr) {
        const ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to create a linked list from a vector of values
ListNode* createList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    auto* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Test function to quickly add and test linked lists
void testRemoveNthFromEnd(const vector<int>& values, int n) {
    ListNode* head = createList(values);
    cout << "Original list: ";
    printList(head);

    head = Solution::removeNthFromEnd(head, n);
    cout << "Modified list after removing " << n << "-th node from the end: ";
    printList(head);

    deleteList(head);
    cout << endl;
}

// Example usage
int main() {
    // Test cases
    testRemoveNthFromEnd({1, 2}, 1);            // Removing the last node
    testRemoveNthFromEnd({1, 2, 3, 4, 5}, 2);   // Removing the 2nd node from the end
    testRemoveNthFromEnd({1}, 1);               // Removing the only node
    testRemoveNthFromEnd({1, 2, 3}, 3);         // Removing the head node
    testRemoveNthFromEnd({}, 1);                // Edge case: Empty list

    return 0;
}