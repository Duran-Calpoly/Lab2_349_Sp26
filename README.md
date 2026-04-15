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

---

## 🌲 Lab 2, Day 2: DFS & Connected Components

In this lab, you are provided with a fully functional, instrumented Depth-First Search (DFS) implementation. Your goal is to use this tool to explore how different graph structures impact **recursion depth** and **execution efficiency**.

### 🎯 Today's Goals
* **Trace** an existing DFS implementation to understand its "backtracking" logic.
* **Verify** the algorithm by building a custom disconnected graph and predicting the result.
* **Analyze** the "Stack Depth" metrics to understand why some graphs are riskier to process than others.

---

### 🛠️ Task 1: Custom Graph & Prediction
Open `test_2_2.cc`. I have provided the testing harness, but the graph is currently empty. 

**Your Task:**
1.  **Construct a Graph:** Using `g.addEdge()`, build an undirected graph with at least **8 vertices**.
2.  **Force Disconnection:** Intentionally leave the graph disconnected. Create at least 3 distinct "islands" (Connected Components).
3.  **Predict:** Before running the code, manually count how many components you created.
4.  **Edit the Assert:** Change the `assert(res.numComponents == X)` line to match your prediction.

#### ✅ Run the Logic Test
Compile and run to see if your prediction matches the algorithm's output:
```bash
g++ -I../day1 ../day1/graph.cc dfs.cc test_2_2.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: Measurement (The Chain vs. The Forest)
Now that you’ve verified the logic, it's time to look at the "engineering metrics." We are going to compare two graphs with the same number of vertices (5,000) but completely different shapes.

Run the `day2.cc` measurement script:
```bash
g++ -I../day1 ../day1/graph.cc dfs.cc day2.cc -o day2_timer && ./day2_timer
```

**Look closely at the output for:**
* **Max Recursion Depth:** How deep did the stack go?
* **Edges Examined:** How many times did the code look at an edge?

---

### 🧠 Reflection Questions (For Sign-Off)
I will ask you at least one of these when you come up for your signature:

1.  **The Stack Risk:** Your results should show a **Max Recursion Depth of 5,000** for the Chain. If we increased this to 100,000, why would the program likely crash, and how would you fix it without changing the DFS logic?
2.  **The Instrumentation:** Look at `dfs.cc`. How does the code track the `max_depth_reached`? Why do we decrement `current_depth` at the end of the helper function?
3.  **Undirected Math:** Why does the "Chain" experiment show exactly **9,998** edges examined for 5,000 vertices? (Hint: Think about the definition of a path and the fact that the graph is undirected).

---
## 🚀 Lab 2, Day 3: BFS & Shortest Paths (4/20)

Yesterday, we saw how DFS dives deep. Today, we use **Breadth-First Search (BFS)** to explore a graph in "waves." This layer-by-layer approach ensures that we find the absolute shortest path in unweighted networks.

---

### 🎯 Today's Goals
* **Verify** the "Shortest Path" property.
* **Analyze** the memory footprint of "wide" vs. "deep" graphs.
* **Identify** nodes that are disconnected from the start.

---

### 🛠️ Task 1: Custom Paths & Predictions
Open `test_2_3.cc`. 

1.  **Construct a Graph:** Create two different paths between node **0** and node **3**—one path should be 3 edges long, the other should be 2 edges long.
2.  **Predict:** Which path will BFS choose? What will the `distances[3]` value be?
3.  **Run the logic test:**

```bash
g++ -I../day1 ../day1/graph.cc bfs.cc test_2_3.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: Linear vs. Hub Measurements
Now it's time to measure the "frontier" of the search. We are comparing **The Chain** ($V$ nodes in a line) vs. **The Star** (1 center node connected to all others). Run the `day3.cc` experiment:

```bash
g++ -I../day1 ../day1/graph.cc bfs.cc day3.cc -o day3_timer && ./day3_timer
```

---

### 🧠 Reflection Questions (For Sign-Off)

> **Note:** Be ready to discuss these results at the front desk to receive your daily signature.

* **The "Unidentified" State:** If a node is completely disconnected from your start node, what value does the `distances` vector hold for it?
* **Queue Memory:** In the "Star" experiment, your **Peak Queue Size** will be nearly $V$. In the "Chain," it will be $1$. Why does the hub structure put so much more pressure on memory (the queue) than the linear structure?
* **Time vs. Space:** Both experiments have the same number of vertices and roughly the same number of edges ($O(V+E)$). Why is the "Star" graph usually faster to process despite using more memory for the queue?

---
## 🚀 Lab 2, Day 4: Topological Sort (4/22)

Topological Sort is the process of linearizing a **Directed Acyclic Graph (DAG)** such that for every directed edge $u \to v$, $u$ comes before $v$ in the ordering. Think of this as finding a valid sequence to take college courses based on their prerequisites.



---

### 🎯 Today's Goals
* **Model** a dependency graph and predict a valid topological ordering.
* **Compare** the performance of Kahn's Algorithm vs. a DFS-based approach.
* **Detect** when a valid ordering is "unidentified" due to cycles.

---

### 🛠️ Task 1: Prerequisites & Predictions
Open `test_2_4.cc`.

1.  **Construct a Graph:** Create a DAG representing a small set of tasks with dependencies.
2.  **Predict:** Manually derive one valid topological sort. (Note: There can be multiple correct answers!)
3.  **Run the logic test:**

```bash
g++ -I../day1 ../day1/graph.cc toposort.cc test_2_4.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: Kahn vs. DFS Showdown
Run the `day4.cc` experiment to compare the two methods on a long path and a cyclic graph.

```bash
g++ -I../day1 ../day1/graph.cc toposort.cc day4.cc -o topo_timer && ./topo_timer
```

---

### 🧠 Reflection Questions (For Sign-Off)

> **Note:** Have your terminal output ready and be prepared to answer these questions.

* **The Cycle Detection:** How does Kahn's algorithm know that a cycle exists? (Hint: Look at the size of the final result vector).
* **The DFS Stack:** In the DFS-based approach, why do we need to **reverse** the result vector at the very end?
* **In-Degrees:** If a graph has multiple nodes with an in-degree of 0, does that mean the topological sort is unique? Why or why not?



## 🚀 Lab 2, Day 5: SCC Showdown (4/24)

Strongly Connected Components (**SCCs**) are the maximal subgraphs where every node is reachable from every other node. Today, we compare **Kosaraju’s Algorithm** (The Two-Pass Elegant) against **Tarjan’s Algorithm** (The One-Pass Specialist).

---

### 🎯 Today's Goals
* **Verify** SCC detection on a custom-built graph.
* **Measure** the "Operation Count" (Edge Examinations) of a two-pass vs. one-pass approach.
* **Analyze** the memory tax of graph transposition.

---

### 🛠️ Task 1: Building the "Island" Test
Open `test_2_5.cc`.

1.  **Construct a Graph:** Create a directed graph with at least **6 vertices** and **2 distinct SCCs**.
2.  **Predict:** Ensure there is a "**bridge**" (a directed edge from SCC A to SCC B, but **NOT** back).
3.  **Run the logic test:**

```bash
g++ -I../day1 ../day1/graph.cc scc.cc test_2_5.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: Measurement (Time, Space, & Ops)
Run the `day5.cc` script to see how the two algorithms handle a giant ring structure. This will output real-world metrics on execution time and the total number of edge lookups performed by each method.

```bash
g++ -I../day1 ../day1/graph.cc scc.cc day5.cc -o scc_timer && ./scc_timer
```

---

### 🧠 Reflection Questions (For Sign-Off)

> **Note:** Be prepared to justify your results when you present your physical sign-off sheet to the instructor.

* **The Transpose Tax:** Look at the "Mem" output for Kosaraju. Why is it significantly higher than Tarjan's memory usage, even for the same graph?
* **Edge Examinations:** Kosaraju usually examines edges twice as many times as Tarjan. Looking at the logic in `scc.cc`, where do those two passes happen?
* **The Single-Pass Advantage:** If you were writing a compiler to analyze millions of lines of code (a massive graph), why might you choose Tarjan even if Kosaraju is easier to write?

## 🚀 Lab 2, Day 6: Dijkstra’s Algorithm (4/27)

Today, we transition from unweighted "hops" to **Weighted Shortest Paths**. In a network where every road has a different speed limit or every server has a different latency, BFS is no longer sufficient. We need **Dijkstra’s Algorithm**.

---

### 🎯 Today's Goals
* **Verify** that Dijkstra correctly prioritizes lower-weight paths over fewer-hop paths.
* **Measure** "Relaxations"—the number of times the algorithm improves its estimate for a node.
* **Analyze** the memory overhead of the Priority Queue (Min-Heap).

---

### 🛠️ Task 1: The "Detour" Test
Open `test_2_6.cc`.

1.  **Construct a Graph:** Create node **0** and node **1**. Connect them with a heavy weight (e.g., **100**).
2.  **Add a Detour:** Create a path through node **2** that is much cheaper (e.g., **10 + 10**).
3.  **Predict:** Even though the detour takes two "hops," Dijkstra should identify it as the shortest path.
4.  **Run the logic test:**

```bash
g++ graph.cc dijkstra.cc test_2_6.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: Measuring Density & Relaxations
Now it's time to see how the "workload" changes based on graph structure. We are comparing a simple line (Sparse) vs. a multi-connected grid (Dense). Run the `day6.cc` experiment:

```bash
g++ graph.cc dijkstra.cc day6.cc -o dijkstra_timer && ./dijkstra_timer
```

---

### 🧠 Reflection Questions (For Sign-Off)

> **Note:** Be ready to show your terminal output and explain these concepts during your physical sign-off.

* **BFS vs. Dijkstra:** If all weights were set to **1**, how would Dijkstra's behavior compare to the BFS we ran on Day 3?
* **PQ Size:** Why does the **Max PQ Size** increase as the graph becomes denser? 
* **Space Complexity:** Aside from the graph itself, what is the $O(V)$ space overhead required to run Dijkstra's? *(Hint: Look at the vectors initialized in `dijkstra.h` and `dijkstra.cc`.)*
* **Relaxations:** Does "Dense" graph result in significantly more relaxations than a "Chain" graph of the same size?

## 🚀 Lab 2, Day 7: Bellman-Ford & Negative Cycles (4/29)

Dijkstra's algorithm is efficient, but it has one major weakness: it is legally blind to **negative edge weights**. In specific systems—like financial arbitrage or energy networks—weights can be negative. However, if a cycle has a **negative total sum**, you could traverse it infinitely to reach a "shortest path" of negative infinity. This effectively "breaks the physics" of graph traversal.


Today, we use **Bellman-Ford** and the **Shortest Path Faster Algorithm (SPFA)** to identify these anomalies and handle negative weights safely.

---

### 🎯 Today's Goals
* **Detect** negative cycles that would cause Dijkstra's algorithm to loop infinitely.
* **Compare** the predictable $O(VE)$ behavior of Bellman-Ford against the queue-optimized SPFA.
* **Identify** why SPFA is a "best-case hero" but shares the same "worst-case nightmare" as Bellman-Ford.

---

### 🛠️ Task 1: The "Physics Breaker" Test
Open `test_2_7.cc`. To avoid the Segmentation Faults seen in previous days, we are using a **localized version** of the Graph module specifically for Day 7.

1.  **Construct a Graph:** Using `g.addEdge()`, build a graph with at least 4 nodes.
2.  **Create a Negative Cycle:** Ensure the sum of edges in a loop (e.g., $1 \to 2 \to 3 \to 1$) is **less than zero**.
3.  **Verify:** Ensure both Bellman-Ford and SPFA report `hasNegativeCycle == true`.
4.  **Run the logic test:**

```bash
g++ graph.cc pathfinder.cc test_2_7.cc -o test_runner && ./test_runner
```

---

### ⏱️ Task 2: SPFA vs. Bellman-Ford
Run the `day7.cc` measurement script. This script compares the standard nested-loop Bellman-Ford against the queue-based SPFA on a linear graph.

```bash
g++ graph.cc pathfinder.cc day7.cc -o path_timer && ./path_timer
```

---

### 🧠 Reflection Questions (For Your Final Sign-Off)

> **Final Sign-Off:** This is your last check-in for the Graph sequence! Be prepared to discuss these results.

* **The V-th Pass:** Bellman-Ford runs for $V-1$ iterations. Why is a **V-th pass** required to definitively catch a negative cycle?
* **SPFA Relaxations:** Look at your "Relaxations" count. Why is SPFA able to achieve the same result as Bellman-Ford with significantly fewer edge examinations?
* **The "Killer" Graph:** If SPFA is generally faster, why is it still categorized as $O(VE)$ in the worst case? Can you describe a graph structure that would force SPFA to re-queue nodes as many times as Bellman-Ford?

---

### 🏁 Submission
3.  **Present your fully completed 7-day Sign-Off Sheet to the instructor.** Congratulations on finishing the Lab 2 Gauntlet! You’ve progressed from basic adjacency lists to detecting systemic failures in weighted networks.
