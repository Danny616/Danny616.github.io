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
    int maxPathSum(const TreeNode* root) {
        maxSum = INT_MIN; // Initialize to the smallest integer
        maxGain(root);
        return maxSum;
    }

private:
    int maxSum = 0;

    int maxGain(const TreeNode* node) {
        if (!node) return 0;

        // Recursively get the maximum gain from left and right subtrees
        const int leftGain = max(maxGain(node->left), 0);   // Ignore paths with negative sums
        const int rightGain = max(maxGain(node->right), 0);

        // Price of the new path that passes through the current node
        const int priceNewPath = node->val + leftGain + rightGain;

        // Update maxSum if it's better to start a new path
        maxSum = max(maxSum, priceNewPath);

        // For recursion: return the max gain if we continue the same path
        return node->val + max(leftGain, rightGain);
    }
};

// Helper function to build a tree from a vector (for testing)
TreeNode* buildTree(const vector<string>& nodes, const int index) {
    if (index >= nodes.size() || nodes[index] == "null") return nullptr;
    auto* node = new TreeNode(stoi(nodes[index]));
    node->left = buildTree(nodes, 2 * index + 1);
    node->right = buildTree(nodes, 2 * index + 2);
    return node;
}

// Example usage:
int main() {
    Solution sol{};

    // Example 1:
    const vector<string> tree1 = {"1", "2", "3"};
    const TreeNode* root1 = buildTree(tree1, 0);
    cout << "Maximum Path Sum (Example 1): " << sol.maxPathSum(root1) << endl; // Output: 6

    // Example 2:
    const vector<string> tree2 = {"-10", "9", "20", "null", "null", "15", "7"};
    const TreeNode* root2 = buildTree(tree2, 0);
    cout << "Maximum Path Sum (Example 2): " << sol.maxPathSum(root2) << endl; // Output: 42

    // Clean up memory
    delete root1;
    delete root2;

    return 0;
}