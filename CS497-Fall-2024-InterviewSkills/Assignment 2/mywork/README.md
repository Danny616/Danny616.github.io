**Problem 1:** The solution uses the Boyer-Moore Voting Algorithm to find the majority element, which appears more than `n/2` times in the array.

- **Approach:**
    - **Phase 1:** Iterate through the array to find a candidate. Maintain a `count` and update the candidate when `count` is zero. Adjust `count` based on whether the current element matches the candidate.
    - **Phase 2:** Verify the candidate by counting its occurrences to ensure it is the majority element.

- **Time Complexity:** O(n) because the array is traversed twice.
- **Space Complexity:** O(1) since only a few variables are used.
---
**Problem 2:** The solution uses the Quickselect algorithm to find the k-th largest element in an unsorted array.

- **Approach:**
    - **Partition Function:** Rearranges elements around a pivot, ensuring elements greater than the pivot are on the left, and elements less than or equal to the pivot are on the right. Returns the pivot’s final position.
    - **QuickSelect Function:** Uses the partition function to recursively narrow down the search for the k-th largest element. Adjusts the search range based on the pivot's position relative to `k`.
    - **FindKthLargest Function:** Calls `quickSelect` with the entire array and the 1-based index `k`, converting it to 0-based (`k - 1`).

- **Time Complexity:**
    - Average Case: O(n)
    - Worst Case: O(n²) (can be improved with randomized pivot selection)

- **Space Complexity:**
    - O(1) additional space (in-place partitioning)
    - O(log n) for the call stack on average and O(n) in the worst case
---
**Problem 3:** The solution uses a bucket sort approach to find the maximum gap between successive elements in the sorted form of an array. The algorithm is designed to run in linear time with linear extra space.

- **Approach:**
  - **Edge Case:** If the array has less than two elements, return `0` as there's no gap to compute.
  - **Calculate Minimum and Maximum:** Find the minimum and maximum elements in the array to determine the range.
  - **Determine Bucket Size and Count:** Calculate the bucket size using `(max_val - min_val) / (n - 1)` to ensure the maximum gap will be at least one of these bucket boundaries. Compute the number of buckets required.
  - **Distribute Elements into Buckets:** Place elements into appropriate buckets, tracking the minimum and maximum values in each bucket.
  - **Calculate Maximum Gap:** Iterate through the buckets to find the maximum gap between the maximum of the previous bucket and the minimum of the current bucket.

- **Time Complexity:**
  - O(n) for distributing elements into buckets and computing the maximum gap.

- **Space Complexity:**
  - O(n) for storing the buckets and their minimum/maximum values.
---
**Problem 4:** The solution uses a greedy algorithm with a stack to remove duplicate letters from a string such that each letter appears only once. The result is the smallest in lexicographical order among all possible results.

- **Approach:**
  - **Count Occurrences:** Use an array to count the occurrences of each character in the string.
  - **Stack for Result Construction:** Use a stack to build the result while ensuring each character appears only once. A boolean array tracks characters already in the stack.
  - **Greedy Insertion:** Iterate through the string, using the stack to maintain the smallest lexicographical order:
    - For each character, if it's not already in the stack, pop characters from the stack that are greater than the current character and have further occurrences in the remaining string.
    - Push the current character onto the stack and mark it as present.
  - **Construct Result:** Join the characters in the stack to form the final string.

- **Time Complexity:**
  - O(n), where `n` is the length of the string, since each character is processed at most twice.

- **Space Complexity:**
  - O(1) extra space, limited by the constant number of possible lowercase English letters (26).