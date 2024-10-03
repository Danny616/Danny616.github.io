#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(const int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    unordered_map<int, size_t> inorder_index_map;

    TreeNode* buildTreeHelper(vector<int>& preorder, const size_t preorder_left, const size_t preorder_right,
                              vector<int>& inorder, const size_t inorder_left, const size_t inorder_right) {
        // Base case: if there are no elements to construct the tree
        if (preorder_left > preorder_right || inorder_left > inorder_right) {
            return nullptr;
        }

        // The first element in preorder is the root
        const int root_val = preorder[preorder_left];
        auto* root = new TreeNode(root_val);

        // Find the index of the root in inorder traversal
        const size_t inorder_root_index = inorder_index_map[root_val];

        // Number of nodes in the left subtree
        const size_t left_subtree_size = inorder_root_index - inorder_left;

        // Recursively build the left subtree
        root->left = buildTreeHelper(preorder, preorder_left + 1, preorder_left + left_subtree_size,
                                     inorder, inorder_left, inorder_root_index - 1);

        // Recursively build the right subtree
        root->right = buildTreeHelper(preorder, preorder_left + left_subtree_size + 1, preorder_right,
                                      inorder, inorder_root_index + 1, inorder_right);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Edge case: if the traversal lists are empty
        if (preorder.empty() || inorder.empty()) {
            return nullptr;
        }

        // Build a hash map to get index of value in inorder traversal in O(1) time
        for (size_t i = 0; i < inorder.size(); ++i) {
            inorder_index_map[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, 0, preorder.size() - 1,
                               inorder, 0, inorder.size() - 1);
    }
};

// Helper function to print the tree in level order (used for testing)
void printTree(TreeNode* root) {
    if (!root) return;
    vector<TreeNode*> queue = {root};
    vector<string> output;
    size_t index = 0;
    while (index < queue.size()) {
        const TreeNode* node = queue[index++];
        if (node) {
            output.push_back(to_string(node->val));
            queue.push_back(node->left);
            queue.push_back(node->right);
        } else {
            output.emplace_back("null");
        }
    }
    // Remove trailing "null"s
    while (!output.empty() && output.back() == "null") {
        output.pop_back();
    }
    // Print the output
    for (const string& val : output) {
        cout << val << " ";
    }
    cout << endl;
}

// Helper function to delete the tree and free memory
void deleteTree(const TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Example usage
int main() {
    Solution solution;

    // Example 1:
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};
    TreeNode* tree1 = solution.buildTree(preorder1, inorder1);
    printTree(tree1); // Output: 3 9 20 null null 15 7
    deleteTree(tree1); // Free allocated memory

    // Example 2:
    vector<int> preorder2 = {-1};
    vector<int> inorder2 = {-1};
    TreeNode* tree2 = solution.buildTree(preorder2, inorder2);
    printTree(tree2); // Output: -1
    deleteTree(tree2); // Free allocated memory

    return 0;
}
