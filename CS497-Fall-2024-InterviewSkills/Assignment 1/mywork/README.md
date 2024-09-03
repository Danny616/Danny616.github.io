**Problem 1:** The solution uses a hash map (unordered_map) to store each number's index as we iterate through the array. This allows us to check for the required complement (i.e., target - current value) efficiently.
- Approach: We use an unordered map to keep track of the indices of the elements we have seen so far. For each element, we check if its complement (i.e., target - current element) exists in the map. If it does, we have found our solution.
- Time Complexity: The solution operates in O(n) time, where n is the number of elements in the array, because each lookup and insertion operation in the unordered map is O(1) on average.

**Problem 2:** The solution uses a binary search approach with two helper functions to find the leftmost and rightmost indices of the target value in a sorted array.
- Approach: We employ two binary search functions: one to find the first occurrence of the target (left boundary) and another to find the last occurrence (right boundary) by adjusting search boundaries based on comparisons.
- Time Complexity: The solution runs in O(log n) time since each helper function performs a binary search on the array, making it efficient for large datasets.

**Problem 3:** 
- Approach:
- Time Complexity:

**Problem 4:** 
- Approach:
- Time Complexity:

**Problem 5:** 
- Approach:
- Time Complexity:
