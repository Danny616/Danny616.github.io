#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};

// Solution class
class Solution {
public:
    int maxSum;

    // Helper function to compute the maximum gain from each node
    int maxGain(const TreeNode* node) {
        if (node == nullptr) return 0;

        // Recursively call maxGain on left and right children
        int leftGain = max(maxGain(node->left), 0);   // Ignore negative gains
        int rightGain = max(maxGain(node->right), 0); // Ignore negative gains

        // Price to start a new path where 'node' is the highest node
        int priceNewpath = node->val + leftGain + rightGain;

        // Update maxSum if priceNewpath is better
        maxSum = max(maxSum, priceNewpath);

        // Return the maximum gain if continuing the same path
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(const TreeNode* root) {
        maxSum = INT_MIN;
        maxGain(root);
        return maxSum;
    }
};

// Function to split the input string into tokens separated by spaces
vector<string> split(const string &s) {
    vector<string> tokens;
    string item;
    stringstream ss(s);

    while (ss >> item) {
        tokens.push_back(item);
    }
    return tokens;
}

// Function to build the binary tree from the input vector
TreeNode* buildTree(const vector<string> &nodes) {
    if (nodes.empty()) return nullptr;

    TreeNode* root = nullptr;
    queue<TreeNode**> q;
    q.push(&root);

    size_t i = 0;
    while (!q.empty() && i < nodes.size()) {
        TreeNode** ppNode = q.front();
        q.pop();

        if (nodes[i] != "null") {
            int val = stoi(nodes[i]);
            *ppNode = new TreeNode(val);
            q.push(&((*ppNode)->left));
            q.push(&((*ppNode)->right));
        }
        i++;
    }
    return root;
}

// Function to delete the binary tree and free memory
void deleteTree(const TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    string inputLine;
    getline(cin, inputLine);

    // Split the input into tokens
    vector<string> nodes = split(inputLine);

    // Build the tree from the input
    TreeNode* root = buildTree(nodes);

    // Compute the maximum path sum
    Solution solution{};
    int result = solution.maxPathSum(root);

    // Output the result
    cout << result << endl;

    // Free the allocated memory
    deleteTree(root);

    return 0;
}