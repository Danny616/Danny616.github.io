**Problem 1:**  
Given a singly-linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.

**Approach:**
- **Step 1**: Calculate the length of the linked list to determine how many nodes will be in the tree.
- **Step 2**: Use a recursive approach to construct the BST. The middle element of the linked list becomes the root of the tree, and the left and right sublists are recursively built into left and right subtrees, respectively.
- **Step 3**: Maintain a pointer (`currentNode`) to access the linked list elements in order during BST construction.

**Time Complexity:**
**O(n)**, where `n` is the number of elements in the linked list. Each node is processed once.

**Space Complexity:**
**O(log n)**, where `n` is the number of elements, due to the recursive depth of function calls.

---
**Problem 2:**  
Given two integer arrays `preorder` and `inorder`, where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct the binary tree.

**Approach:**
- **Step 1**: Use the first element of `preorder` as the root of the binary tree. The root element divides `inorder` into two parts: the left subtree and the right subtree.
- **Step 2**: Use a recursive approach to construct left and right subtrees. The size of the left subtree can be determined by the position of the root in the `inorder` array.
- **Step 3**: Use a hash map (`inorder_index_map`) to store the index of each value in the `inorder` array for O(1) lookups.

**Time Complexity:**
**O(n)**, where `n` is the number of nodes. Each node is processed once, and hash map lookups are constant time.

**Space Complexity:**
**O(n)** for the hash map and the recursive stack.

---
**Problem 3:**  
Given the root of a binary tree, return an array of the largest value in each row (i.e., each level) of the tree.

**Approach:**
- **Step 1**: Use Breadth-First Search (BFS) to traverse the tree level by level.
- **Step 2**: For each level, initialize `max_value` to store the largest value at that level. As nodes are processed, update `max_value` accordingly.
- **Step 3**: Enqueue the left and right children of the current node to process the next level. Repeat for all levels.

**Time Complexity:**
**O(n)**, where `n` is the number of nodes in the tree. Each node is processed once.

**Space Complexity:**
**O(n)** for the queue used to store nodes at each level.

---
**Problem 4:**  
Given the root of a binary search tree (BST), return a balanced BST with the same node values. A balanced BST is defined as a tree where the depth of the two subtrees of every node never differs by more than one.

**Approach:**
- **Step 1**: Perform an in-order traversal of the original BST to collect node values in a sorted array.
- **Step 2**: Use the sorted array to construct a balanced BST. The middle element of the array becomes the root, ensuring the left and right subtrees are balanced. This is done recursively for each subtree.

**Time Complexity:**
**O(n)**, where `n` is the number of nodes. The in-order traversal and BST construction each take O(n).

**Space Complexity:**
**O(n)** for storing node values in an array and for the recursive stack.

---
**Problem 5:**  
Given an integer array `preorder` where `preorder` is the preorder traversal of a BST, construct the binary search tree.

**Approach**
- **Step 1**: Use the first element of `preorder` as the root.
- **Step 2**: For each subsequent element, traverse down the tree, comparing the current element to the root. Insert smaller values into the left subtree and larger values into the right subtree.
- **Step 3**: Repeat the process for all elements of the `preorder` list to reconstruct the BST.

**Time Complexity:**
**O(n)**, where `n` is the number of nodes, since each node is inserted exactly once.

**Space Complexity:**
**O(n)** for the recursive stack when constructing the tree.

---