# 🕸️ Lab 2: Graph Algorithms & Empirical Analysis
### CSC 349: Analysis of Algorithms — Spring 2026

**Lab 2** moves into the non-linear world of **Graphs**. Graphs are the backbone of modern engineering—from social network connectivity and GPS routing to AI decision trees and compiler optimization.

Following our established style, the goal isn't just to make the code "work." The goal is to **measure**, **analyze**, and **understand** the trade-offs between different data structures and algorithmic approaches.

---

## 📅 Lab Schedule (4/15 – 4/29)

This is a **7-day cumulative lab**. Each day focuses on a specific aspect of graph theory. You are expected to complete the daily task and receive a physical sign-off before the end of the lab period.

| Date | Day | Topic | Key Comparison/Focus |
| :--- | :--- | :--- | :--- |
| **4/15** | Day 1 | **Representation** | Adjacency List vs. Adjacency Matrix |
| **4/17** | Day 2 | **DFS** | Cycle Detection & Recursion Depth |
| **4/20** | Day 3 | **BFS** | Shortest Unweighted Paths |
| **4/22** | Day 4 | **Topological Sort** | DFS-based vs. Kahn’s Algorithm |
| **4/24** | Day 5 | **SCCs** | Kosaraju’s vs. Tarjan’s Algorithm |
| **4/27** | Day 6 | **Dijkstra's** | Priority Queues & Weighted Paths |
| **4/29** | Day 7 | **Bellman-Ford** | Negative Weights & Negative Cycles |

---

## 📝 The Sign-Off Protocol

Just like Lab 1, your grade is tracked via a **Physical Sign-Off Sheet**. 

1.  **Complete the Task:** Write the code, run the provided tests, and generate the timing/measurement data.
2.  **Analysis:** Be ready to explain your results. I will likely ask you one or two "pressure-test" questions about the time complexity or specific behavior of the day's algorithm.
3.  **Signature:** Once I’m satisfied with your explanation, I will sign your sheet. 
4.  **Final Submission:** On **April 29**, you will turn in your fully completed and signed sheet. **Do not lose this paper.**

---

## 🚀 Day 1 (4/15): Graph Representation

Today, we address the fundamental question: **How do we store a graph in memory?** We will compare the **Adjacency Matrix** (constant time edge lookups) against the **Adjacency List** (memory efficiency for sparse data).

### ✅ 1. Implementation & Logic Test
Open `test_2_1.cc`. Your task is to implement a **non-trivial undirected graph** with at least **6 vertices** and **8 edges**.
* **Directed vs. Undirected:** Since our base interface is directed, remember that an undirected edge $(u, v)$ must be added as both `addEdge(u, v)` and `addEdge(v, u)`.
* **The Hub:** Ensure at least one vertex is a "hub" (connected to 3+ other nodes).

Run the logic test:
```bash
g++ graph.cc test_2_1.cc -o test_runner && ./test_runner
```

### ⏱️ 2. Measurement: The Sparse Stress Test
Now, run the `day1.cc` script. This will simulate a sparse network of **5,000 nodes**. Pay close attention to the **Estimated Space Usage** and the time it takes to **Remove** edges.

```bash
g++ graph.cc day1.cc -o day1_timer && ./day1_timer
```

### 🧠 Reflection Questions
* Why does the **Adjacency List** take longer to remove an edge even though it uses significantly less memory?
* At what point (edge density) does an **Adjacency Matrix** become more "efficient" than a list?
* How does the "Contiguous Memory" of a matrix help with CPU performance?
