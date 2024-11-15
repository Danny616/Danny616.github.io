## Problem 1: Find if Path Exists in Graph

The code determines if there is a valid path between two nodes in an undirected graph.

### Approach:

- **Union-Find:**
    - Use Union-Find to group nodes into connected components.
    - Each edge connects two nodes, so we `unite` them in the same component.
    - Finally, check if the source and destination nodes belong to the same component using `find`.

### Time Complexity:

- **O(E ⋅ α(n)):** Processing all edges with almost constant-time Union-Find operations.
- **O(E log E):** If sorting is involved (for Kruskal's).

### Space Complexity:

- **O(n):** Space for the parent and rank arrays.

---

## Problem 2: Longest Cycle in a Graph

The code finds the length of the longest cycle in a directed graph represented by an adjacency list where each node has at most one outgoing edge.

### Approach:

- **Depth-First Search (DFS)**:
  - Traverse the graph using DFS, marking nodes as:
    - `0`: Unvisited
    - `1`: Visiting
    - `2`: Fully visited
  - Use a `dist` array to keep track of the depth of each node during DFS.
  - Detect a cycle when revisiting a node marked as `1` (currently being visited) and calculate its length using the depth difference.
- **Cycle Detection**:
    - If a node revisits another node in the current path, compute the cycle length as `current_depth - dist[revisited_node] + 1`.
    - Keep track of the maximum cycle length encountered.

### Time Complexity:

- **O(V + E):** Each node (`V`) and edge (`E`) is processed at most once during DFS.

### Space Complexity:

- **O(V):** Space is required for the `state` and `dist` arrays, as well as the recursion stack.

---

## Problem 3: Connecting Cities with Minimum Cost

The code finds the minimum cost to connect all cities in a graph using edges with weights.

### Approach:

- **Kruskal's Algorithm:**
    - Sort all edges by weight.
    - Use Union-Find to connect components while avoiding cycles.
    - Add edges until all cities are connected or return `-1` if impossible.

### Time Complexity:

- **O(E log E):** For sorting the edges.
- **O(E ⋅ α(n)):** For Union-Find operations.

### Space Complexity:

- **O(n):** For Union-Find parent and rank arrays.

---

## Problem 4: All Paths From Source to Target

The code finds all possible paths in a directed acyclic graph (DAG) from the source node to the target node.

### Approach:

- **DFS with Backtracking:**
    - Recursively traverse the graph, maintaining the current path.
    - When reaching the target node, save the path in the result.
    - Backtrack to explore other paths.

### Time Complexity:

- **O(V + E):** Each node and edge is processed once in DFS.

### Space Complexity:

- **O(V):** For the recursion stack and storing the current path.

---

## Problem 5: Pow(x, n)

The code computes \(x^n\) (x raised to the power n) efficiently.

### Approach:

- **Exponentiation by Squaring:**
    - If \(n\) is odd, multiply the result by \(x\).
    - Square \(x\) and halve \(n\) to reduce the problem size iteratively.
    - Handle negative powers by computing \(1/x\) for the base and using positive \(n\).

### Time Complexity:

- **O(log n):** Reduces the problem size by half in each step.

### Space Complexity:

- **O(1):** Iterative approach uses constant space.

---