#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(const int x) : val(x), next(nullptr) {}
};

// Definition for binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    ListNode* currentNode = nullptr;

public:
    TreeNode* sortedListToBST(ListNode* head) {
        // Calculate the length of the linked list
        const int n = getLength(head);
        currentNode = head;
        // Build the BST using the helper function
        return buildBST(0, n - 1);
    }

private:
    // Helper function to calculate the length of the list
    static int getLength(const ListNode* head) {
        int length = 0;
        while (head != nullptr) {
            ++length;
            head = head->next;
        }
        return length;
    }

    // Recursive helper function to build the BST
    TreeNode* buildBST(const int left, const int right) {
        if (left > right) {
            return nullptr;
        }

        const int mid = left + (right - left) / 2;

        // Recursively build the left subtree
        TreeNode* leftChild = buildBST(left, mid - 1);

        // The currentNode now points to the middle node of the linked list
        const auto root = new TreeNode(currentNode->val);
        currentNode = currentNode->next;

        // Recursively build the right subtree
        TreeNode* rightChild = buildBST(mid + 1, right);

        // Assign left and right children to the root
        root->left = leftChild;
        root->right = rightChild;

        return root;
    }
};

// Function to delete the linked list and free memory
void deleteLinkedList(const ListNode* head) {
    while (head != nullptr) {
        const ListNode* temp = head->next;
        delete head;
        head = temp;
    }
}

// Function to delete the BST and free memory
void deleteBST(const TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    // Recursively delete left and right subtrees
    deleteBST(root->left);
    deleteBST(root->right);
    // Delete the current node
    delete root;
}

// Function to print the linked list
void printLinkedList(const ListNode* head) {
    cout << "Linked List: ";
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

// In-order traversal to print the BST
void printInOrderBST(const TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    printInOrderBST(root->left);
    cout << root->val << " ";
    printInOrderBST(root->right);
}

int main() {
    // Create the linked list [-10, -3, 0, 5, 9]
    auto* head = new ListNode(-10);
    head->next = new ListNode(-3);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(9);

    // Print the linked list
    printLinkedList(head);

    Solution solution{};
    const TreeNode* bstRoot = solution.sortedListToBST(head);

    // Print the BST in-order (should be sorted)
    cout << "BST In-order Traversal: ";
    printInOrderBST(bstRoot);
    cout << endl;

    // After using the BST, delete it to free memory
    deleteBST(bstRoot);

    // Delete the linked list to free memory
    deleteLinkedList(head);

    return 0;
}