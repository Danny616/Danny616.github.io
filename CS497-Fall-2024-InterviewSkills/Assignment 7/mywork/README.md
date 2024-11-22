## Problem 1: Course Schedule

The code determines if it is possible to finish all courses given a set of prerequisites. It solves the problem using a graph traversal technique to detect if the directed graph representing course dependencies has a cycle.

### Approach:

- **Topological Sorting using BFS (Kahn's Algorithm):**
  - Represent the course prerequisites as a directed graph using an adjacency list.
  - Use an in-degree array to keep track of the number of incoming edges for each course.
  - Add all courses with zero in-degree to a queue.
  - Perform BFS, decrementing the in-degree of adjacent nodes and adding them to the queue when their in-degree reaches zero.
  - Count the number of courses visited during BFS.
  - If the number of visited courses equals the total number of courses, return `true`; otherwise, return `false`.

### Time Complexity:

- **O(V + E):**
  - \(V\): Number of courses (nodes).
  - \(E\): Number of prerequisite pairs (edges).
  - Constructing the adjacency list and processing the nodes and edges in BFS both take linear time.

### Space Complexity:

- **O(V + E):**
  - \(V\): Space for the adjacency list and in-degree array.
  - \(E\): Space for the edges in the adjacency list.

---

## Problem 2: Network Delay Time

The code computes the time it takes for a signal to reach all nodes in a network, starting from a given source node. It solves the problem using **Dijkstra's Algorithm** to find the shortest path from the source to all other nodes.

### Approach:

- **Graph Representation:**
  - The network is represented as a directed weighted graph using an adjacency list, where each edge has a travel time.

- **Dijkstra's Algorithm:**
  - Use a priority queue (min-heap) to process nodes in increasing order of distance from the source.
  - Maintain a distance array to store the shortest time to each node.
  - Update the distances for neighboring nodes if a shorter path is found, and add them to the priority queue.

- **Result Calculation:**
  - After processing all nodes, determine the maximum time in the distance array.
  - If any node is unreachable (distance is still `INT_MAX`), return `-1`.

### Time Complexity:

- **O((V + E) log V):**
  - \(V\): Number of nodes.
  - \(E\): Number of edges.
  - Each edge is processed once, and priority queue operations cost \(O(\log V)\).

### Space Complexity:

- **O(V + E):**
  - \(V\): Space for the distance array and priority queue.
  - \(E\): Space for the adjacency list representation of the graph.

---

## Problem 3: Minimum Cost to Supply Water

The code determines the minimum cost to supply water to all houses in a village by either digging wells or connecting houses using pipes. It solves the problem using **Kruskal's Algorithm** to find the Minimum Spanning Tree (MST).

### Approach:

- **Virtual Node Representation:**
  - Introduce a virtual node (node `0`) representing a well. Each well is connected to a house with a cost equal to the well's installation cost.
  - Combine the virtual edges (wells) and actual edges (pipes) into a single list.

- **Edge Sorting:**
  - Sort all edges by cost in ascending order to process the cheapest edges first.

- **Kruskal's Algorithm:**
  - Use a Union-Find (Disjoint Set Union) structure to process edges.
  - Add an edge to the MST if it connects two previously unconnected components.
  - Keep adding edges until all houses are connected.

- **Result:**
  - The total cost of all edges in the MST is the minimum cost to supply water.

### Time Complexity:

- **O(E log E):**
  - \(E\): Total number of edges, including \(n\) virtual edges for wells and existing pipes.
  - Sorting the edges takes \(O(E \log E)\), and Union-Find operations are nearly constant time (\(O(\alpha(n))\)).

### Space Complexity:

- **O(E + n):**
  - \(E\): Space for the edges.
  - \(n\): Space for the Union-Find parent and rank arrays.

---

## Problem 4: Ride Service Management System

This code implements a simplified ride-hailing service, managing users, drivers, rides, and payments. It includes functionality for booking rides, tracking driver locations, managing ride statuses, and processing payments.

### Approach:

1. **Classes and Their Responsibilities:**
  - **`Location`:** Represents a geographic location with latitude and longitude and calculates distances.
  - **`User`:** Maintains user details and ride history.
  - **`Driver`:** Maintains driver details, availability, and rating.
  - **`Ride`:** Represents a ride with details about the user, driver, pickup, drop-off, price, and status.
  - **`PaymentProcessor`:** Handles payment and refund processing.
  - **`RideService`:** Orchestrates interactions between users, drivers, and rides.

2. **Key Functionalities:**
  - **Finding Nearby Drivers:** Filters available drivers within a specified radius using Euclidean distance.
  - **Booking a Ride:** Assigns the nearest driver to the user, calculates the price, and updates statuses.
  - **Tracking and Updating Locations:** Tracks the current location of a driver and updates it as needed.
  - **Ride Completion:** Updates ride status, processes payments, and updates driver ratings.
  - **Ride Cancellation:** Cancels rides with optional cancellation fees and processes refunds.
  - **Displaying Receipts:** Shows ride details, including price and status.

3. **Workflow:**
  - Users and drivers are added to the system.
  - Users can check for nearby available drivers, book rides, and view receipts.
  - Drivers' locations and statuses are updated dynamically.
  - Payment processing is automated for completed or canceled rides.

### Time Complexity:

- **Finding Nearby Drivers:**
  - **O(d):** Where \(d\) is the number of drivers. Filters drivers within the radius.
- **Booking a Ride:**
  - **O(d):** Finds nearby drivers and assigns the nearest one.
- **Ride Management:**
  - **O(1):** For updating statuses or locations.

### Space Complexity:

- **O(u + d + r):**
  - \(u\): Number of users.
  - \(d\): Number of drivers.
  - \(r\): Number of rides.

### Example Scenarios:

- **Scenario 1: User Completes a Ride**
  - User books a ride, driver updates location, and ride is completed with a rating.
  - Receipt is displayed after payment is processed.

- **Scenario 2: User Cancels a Ride**
  - User books a ride but cancels it before completion.
  - Cancellation fees and refunds are processed, and ride status is updated.

This system demonstrates a modular and scalable approach to building a ride-hailing service.
