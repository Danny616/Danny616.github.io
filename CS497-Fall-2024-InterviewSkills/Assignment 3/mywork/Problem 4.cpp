#include <vector>
#include <iostream>
#include <queue>
#include <climits> // for INT_MIN

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    static vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result; // Return empty vector if the tree is empty
        }

        queue<TreeNode*> q;
        q.push(root); // Start BFS from the root

        while (!q.empty()) {
            const size_t level_size = q.size(); // Number of nodes at the current level
            int max_value = INT_MIN; // Initialize max value for this level

            // Process all nodes at the current level
            for (size_t i = 0; i < level_size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                max_value = max(max_value, node->val); // Update max value

                // Enqueue left and right children if they exist
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }

            result.push_back(max_value); // Add the largest value of this level to the result
        }

        return result; // Return the list of largest values for each level
    }
};

void deleteTree(const TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Example usage:
int main() {
    // Build the tree for Example 1: [1,3,2,5,3,null,9]
    auto* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);

    vector<int> result = Solution::largestValues(root);

    // Output the result
    for (const int val : result) {
        cout << val << " ";
    }
    // Expected Output: 1 3 9

    // Clean up the allocated memory
    deleteTree(root);

    return 0;
}