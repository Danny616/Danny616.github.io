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