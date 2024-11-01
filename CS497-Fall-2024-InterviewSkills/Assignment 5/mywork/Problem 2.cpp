#include <iostream>
#include <climits>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    Solution() : minDiff(INT_MAX), prev(-1) {} // Constructor to initialize fields

    int minDiffInBST(const TreeNode* root) {
        inorder(root);
        return minDiff;
    }

private:
    int minDiff;
    int prev;

    void inorder(const TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (prev != -1) {
            minDiff = min(minDiff, node->val - prev);
        }
        prev = node->val;
        inorder(node->right);
    }
};

// Example usage:
int main() {
    // Construct the BST for Example 1: [4,2,6,1,3]
    auto* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    const int result = sol.minDiffInBST(root);
    cout << "Minimum absolute difference is: " << result << endl;

    // Clean up memory
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}