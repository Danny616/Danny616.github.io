**Problem 1:** The solution uses a hash map (unordered_map) to store each number's index as we iterate through the array. This allows us to check for the required complement (i.e., target - current value) efficiently.
- Approach: We use an unordered map to keep track of the indices of the elements we have seen so far. For each element, we check if its complement (i.e., target - current element) exists in the map. If it does, we have found our solution.
- Time Complexity: The solution operates in O(n) time, where n is the number of elements in the array, because each lookup and insertion operation in the unordered map is O(1) on average.

**Problem 2:** The solution uses a binary search approach with two helper functions to find the leftmost and rightmost indices of the target value in a sorted array.
- Approach: We employ two binary search functions: one to find the first occurrence of the target (left boundary) and another to find the last occurrence (right boundary) by adjusting search boundaries based on comparisons.
- Time Complexity: The solution runs in O(log n) time since each helper function performs a binary search on the array, making it efficient for large datasets.

**Problem 3:**  The solution finds the median of two sorted arrays using binary search, ensuring efficient partitioning of the arrays.
- Approach: Perform a binary search on the smaller array to find the correct partition such that the left and right partitions of the combined arrays are balanced. Calculate the median based on the partition values.
- Time Complexity: The solution operates in O(log(m + n)) time, where m and n are the sizes of the two arrays, due to the binary search on the smaller array.

**Problem 4:** The solution removes the nth node from the end of a singly-linked list using a two-pointer approach.
- Approach: A dummy node is used alongside two pointers (fast and slow), with the fast pointer moved n+1 steps ahead to identify and remove the nth node from the end efficiently.
- Time Complexity: The solution operates in O(L) time, where L is the length of the linked list, as each node is visited at most once.

**Problem 5:** The solution merges k sorted linked lists into one sorted list using a min-heap (priority queue) to efficiently extract and merge the smallest elements.
- Approach: A priority queue is used to maintain the smallest nodes at the top, allowing for efficient merging by always appending the smallest node to the result list and pushing the next node from the extracted list into the heap.
- Time Complexity: The solution operates in O(N log k) time, where N is the total number of nodes across all lists and k is the number of lists, due to heap operations that log k times for each node.
