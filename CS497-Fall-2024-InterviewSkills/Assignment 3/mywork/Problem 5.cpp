#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    // Constructor to initialize a node with a value
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to perform in-order traversal and collect node values
void inorderTraversal(const TreeNode* root, vector<int>& nodes) {
    if (!root) return;
    inorderTraversal(root->left, nodes);
    nodes.push_back(root->val);
    inorderTraversal(root->right, nodes);
}

// Function to build a balanced BST from sorted node values
TreeNode* buildBalancedBST(const vector<int>& nodes, size_t start, size_t end) {
    if (start >= end) return nullptr;
    size_t mid = start + (end - start) / 2;
    auto* root = new TreeNode(nodes[mid]);
    root->left = buildBalancedBST(nodes, start, mid);
    root->right = buildBalancedBST(nodes, mid + 1, end);
    return root;
}

// Main function to balance the BST
TreeNode* balanceBST(const TreeNode* root) {
    vector<int> nodes;
    // Step 1: Collect node values in sorted order
    inorderTraversal(root, nodes);
    // Step 2: Build a balanced BST from the sorted node values
    return buildBalancedBST(nodes, 0, nodes.size());
}

// Helper function to print the tree in-order (for testing purposes)
void printInOrder(const TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

// Function to delete the tree and free memory
void deleteTree(const TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Example usage
int main() {
    // Constructing the unbalanced BST from Example 2
    auto* root = new TreeNode(2);
    root->right = new TreeNode(1);
    root->right->right = new TreeNode(3);

    // Balancing the BST
    TreeNode* balancedRoot = balanceBST(root);

    // Printing the balanced BST in-order (should be same as the original sorted values)
    cout << "In-order traversal of the balanced BST: ";
    printInOrder(balancedRoot);
    cout << endl;

    // Clean up memory
    deleteTree(root);          // Delete the original tree
    deleteTree(balancedRoot);  // Delete the balanced tree

    return 0;
}
