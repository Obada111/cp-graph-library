# 🔥 ULTIMATE GRAPH CLASS - Complete Professional Guide

[![C++](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Algorithms](https://img.shields.io/badge/Algorithms-8%20Complete-brightgreen.svg)]()
[![Status](https://img.shields.io/badge/Status-Production%20Ready-success.svg)]()

> 🎯 **The Most Complete Graph Implementation with All Major Algorithms**
>
> Master **BFS**, **DFS**, **Dijkstra**, **Bellman-Ford**, **Floyd-Warshall**, **Topological Sort**, **Kosaraju's SCC**, **Prim's MST**, and **Kruskal's MST** with professional C++ code and detailed explanations

---

## 📚 Table of Contents

- [What is a Graph?](#-what-is-a-graph)
- [Graph Representations](#-graph-representations)
- [Class Overview](#-class-overview)
- [All 8 Algorithms](#-all-8-algorithms)
  - [1. BFS - Breadth First Search](#1-bfs-breadth-first-search)
  - [2. Dijkstra's Algorithm](#2-dijkstras-algorithm)
  - [3. Bellman-Ford Algorithm](#3-bellman-ford-algorithm)
  - [4. Floyd-Warshall Algorithm](#4-floyd-warshall-algorithm)
  - [5. Topological Sort](#5-topological-sort)
  - [6. Kosaraju's SCC](#6-kosakus-scc)
  - [7. Prim's MST](#7-prims-mst)
  - [8. Kruskal's MST](#8-kruskals-mst)
- [Complete Code Explanation](#-complete-code-explanation)
- [Usage Examples](#-usage-examples)
- [Complexity Analysis](#-complexity-analysis)
- [When to Use Each Algorithm](#-when-to-use-each-algorithm)

---

## 📊 What is a Graph?

### Definition

A **Graph** is a non-linear data structure consisting of:
- **Vertices (Nodes):** Individual points/entities
- **Edges:** Connections between vertices
- **Weights (Optional):** Values associated with edges

### Visual Representation

```
═══════════════════════════════════════════════════════
                  GRAPH STRUCTURE
═══════════════════════════════════════════════════════

VERTICES: 0, 1, 2, 3
EDGES: (0,1), (0,2), (1,2), (2,3)
WEIGHTS: Various

           Undirected Graph              Directed Graph
           ─────────────────             ──────────────

               0                              0
              / \                           / \
             1   2                         1   2
              \ /                           \ /
               3                             3

Undirected: Edges go BOTH ways          Directed: Edges go ONE way
  0 ↔ 1 (bidirectional)                  0 → 1 (one direction)


Weighted vs Unweighted
──────────────────────

Unweighted:  0 -- 1 -- 2    (No numbers)
               |   |
               3 --+

Weighted:    0 --5-- 1 --2-- 2    (Numbers = weights)
               |3  |7
               3 --4--+
```

### Types of Graphs

```
1. DIRECTED vs UNDIRECTED
   Directed:   0 → 1 → 2 (one direction)
   Undirected: 0 ↔ 1 ↔ 2 (both directions)

2. WEIGHTED vs UNWEIGHTED
   Weighted:   0 --5--> 1 (edge has value 5)
   Unweighted: 0 -------> 1 (no weight)

3. CYCLIC vs ACYCLIC
   Cyclic:     1 → 2 → 3 → 1 (can return to start)
   Acyclic:    1 → 2 → 3 (cannot return)

4. CONNECTED vs DISCONNECTED
   Connected:     All vertices reachable from any vertex
   Disconnected:  Some vertices unreachable from others
```

---

## 🗂️ Graph Representations

### Adjacency List (Used in Code)

```
═══════════════════════════════════════════════════════
                  ADJACENCY LIST
═══════════════════════════════════════════════════════

Graph:     0 → 1 → 2
           0 → 2 → 3
           1 → 2 → 3
           2 → 3

Adjacency List representation:
0: [(1, weight), (2, weight)]
1: [(2, weight), (3, weight)]
2: [(3, weight)]
3: []

Space: O(V + E)
Access: O(degree of V)
Best for: Sparse graphs, BFS/DFS

C++ Implementation:
vector<vector<pair<int, ll>>> adj;
adj[0] = [(1, w1), (2, w2)]
adj[1] = [(2, w3), (3, w4)]
```

### Adjacency Matrix (Alternative)

```
═══════════════════════════════════════════════════════
               ADJACENCY MATRIX
═══════════════════════════════════════════════════════

       0  1  2  3
   0 [ 0  1  1  0 ]
   1 [ 0  0  1  1 ]
   2 [ 0  0  0  1 ]
   3 [ 0  0  0  0 ]

adj[i][j] = weight of edge from i to j (0 if no edge)

Space: O(V²)
Access: O(1)
Best for: Dense graphs, Floyd-Warshall
```

---

## 📋 Class Overview

### Class Structure

```cpp
class Graph {
public:
    int n;                              // Number of vertices
    bool directed;                      // Is directed?
    vector<vector<pair<int, ll>>> adj;  // Adjacency list
    
    // Constructor
    Graph(int n, bool directed = true);
    
    // Core methods
    void add_edge(int u, int v, ll w = 1);
    
    // Algorithms
    pair<vector<int>, vector<int>> bfs(int s);
    pair<vector<ll>, vector<int>> dijkstra(int s);
    tuple<vector<ll>, vector<int>, bool> bellman_ford(int s);
    pair<vector<vector<ll>>, vector<vector<int>>> floyd_warshall();
    vector<int> topological_sort();
    vector<vector<int>> kosaraju();
    pair<ll, vector<tuple<int, int, ll>>> prim();
    pair<ll, vector<tuple<int, int, ll>>> kruskal();
};
```

### Constants and Types

```cpp
using ll = long long;              // For large weights
const ll INF = 1e18;               // Infinity for dijkstra
const int NINF = -1e9;             // Negative infinity
```

---

## 🎯 All 8 Algorithms

---

## 1. BFS - Breadth First Search

### What is BFS?

**Breadth-First Search** explores vertices level by level:
- Start from source
- Visit all neighbors
- Then visit neighbors' neighbors
- Like ripples in water

### Visual Example

```
═══════════════════════════════════════════════════════
                    BFS PROCESS
═══════════════════════════════════════════════════════

Graph:        0
             / \
            1   2
           /     \
          3       4

BFS from 0:

Step 1: Visit 0 (level 0)
        Queue: [0]
        Visited: [0]

Step 2: Remove 0, add neighbors (1, 2) (level 1)
        Queue: [1, 2]
        Visited: [0, 1, 2]

Step 3: Remove 1, add neighbor (3) (level 2)
        Queue: [2, 3]
        Visited: [0, 1, 2, 3]

Step 4: Remove 2, add neighbor (4)
        Queue: [3, 4]
        Visited: [0, 1, 2, 3, 4]

Step 5: Remove 3, no new neighbors
        Queue: [4]

Step 6: Remove 4, no new neighbors
        Queue: []

Result: BFS order = 0, 1, 2, 3, 4
        Distances: [0, 1, 1, 2, 2]
        Parents: [-1, 0, 0, 1, 2]

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
pair<vector<int>, vector<int>> bfs(int s) {
    vector<int> dist(n, -1);           // Distance from source
    vector<int> parent(n, -1);         // To rebuild path
    queue<int> q;
    
    dist[s] = 0;
    q.push(s);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (auto [v, _] : adj[u]) {   // Check all neighbors
            if (dist[v] == -1) {       // Not visited
                dist[v] = dist[u] + 1; // One more step
                parent[v] = u;         // Remember path
                q.push(v);             // Add to queue
            }
        }
    }
    
    return {dist, parent};
}
```

### Time & Space Complexity

```
Time:   O(V + E)  - Visit each vertex and edge once
Space:  O(V)      - Queue and arrays

Where V = vertices, E = edges
```

### When to Use

```
✓ Shortest path in UNWEIGHTED graph
✓ Level-by-level traversal
✓ Find connected components
✓ Bipartite graph checking
✓ Nearest neighbor search

Example:
- Friend suggestions on Facebook
- GPS navigation (all reachable locations)
- Puzzle solving (minimum moves)
```

---

## 2. Dijkstra's Algorithm

### What is Dijkstra?

**Dijkstra's Algorithm** finds shortest path from source to all vertices:
- Uses WEIGHTED edges
- GREEDY approach
- Always picks nearest unvisited vertex
- NO NEGATIVE weights allowed

### Visual Example

```
═══════════════════════════════════════════════════════
              DIJKSTRA'S PROCESS
═══════════════════════════════════════════════════════

Graph:        0
             /4 \3
            1    2
             \2 /1
              3

Find shortest from 0:

Step 1: dist[0]=0, others=INF
        Visited: none
        Next pick: 0

Step 2: From 0, update neighbors
        dist[1] = 4
        dist[2] = 3
        Visited: {0}
        Next pick: 2 (smallest)

Step 3: From 2, update neighbors
        dist[3] = min(INF, 3+1) = 4
        Visited: {0, 2}
        Next pick: 1 or 3 (both 4, pick 1)

Step 4: From 1, update neighbors
        dist[3] = min(4, 4+2) = 4
        Visited: {0, 2, 1}
        Next pick: 3

Step 5: From 3, no improvements
        Visited: {0, 2, 1, 3}

Result: dist = [0, 4, 3, 4]
        Shortest paths: 0→1 (4), 0→2 (3), 0→3 (4)

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
pair<vector<ll>, vector<int>> dijkstra(int s) {
    vector<ll> dist(n, INF);                  // Distance array
    vector<int> parent(n, -1);
    priority_queue<pair<ll, int>,             // Min-heap
                   vector<pair<ll, int>>,
                   greater<>> pq;
    
    dist[s] = 0;
    pq.emplace(0, s);                         // (distance, vertex)
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d != dist[u]) continue;           // Already processed
        
        for (auto [v, w] : adj[u]) {
            ll new_dist = d + w;
            
            if (new_dist < dist[v]) {         // Found shorter path
                dist[v] = new_dist;
                parent[v] = u;
                pq.emplace(new_dist, v);      // Update priority
            }
        }
    }
    
    return {dist, parent};
}
```

### Time & Space Complexity

```
Time:   O((V + E) log V)  - With priority queue
        - Each vertex processed once: O(V)
        - Each edge relaxed once: O(E)
        - Log V for heap operations
        
Space:  O(V)  - Distance and parent arrays
```

### When to Use

```
✓ Shortest path in WEIGHTED graph
✓ NO negative weights allowed
✓ Single source shortest path
✓ GPS/Map navigation
✓ Network routing

Example:
- Google Maps (shortest route)
- Social network (minimum hops)
- Game pathfinding
- Telecom networks (optimal routes)
```

---

## 3. Bellman-Ford Algorithm

### What is Bellman-Ford?

**Bellman-Ford Algorithm** finds shortest path:
- Works with NEGATIVE weights
- Can DETECT negative cycles
- SLOWER than Dijkstra
- Relaxes edges repeatedly

### Visual Example

```
═══════════════════════════════════════════════════════
           BELLMAN-FORD PROCESS
═══════════════════════════════════════════════════════

Graph:        0 --1--> 1
             /           \
            /             -3
           3              \
            \              v
             ---2---> 2 <---
             
Find shortest from 0 (V-1=2 iterations):

Iteration 1:
  Relax all edges:
  0→1: dist[1] = 1
  0→2: dist[2] = INF
  1→2: dist[2] = 1 + (-3) = -2
  
  dist = [0, 1, -2]

Iteration 2:
  Relax all edges again:
  0→1: dist[1] = min(1, 0+1) = 1
  0→2: dist[2] = -2
  1→2: dist[2] = min(-2, 1+(-3)) = -2
  
  dist = [0, 1, -2]

Check for negative cycle:
  All relaxations done? Yes → No negative cycle

Result: dist = [0, 1, -2]

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
tuple<vector<ll>, vector<int>, bool> bellman_ford(int s) {
    vector<ll> dist(n, INF);
    vector<int> parent(n, -1);
    dist[s] = 0;
    
    // Relax edges V-1 times
    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;
            
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {  // Relaxation
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    updated = true;
                }
            }
        }
        
        if (!updated) break;  // Early termination
    }
    
    // Check for negative cycle
    bool has_negative_cycle = false;
    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                has_negative_cycle = true;
                break;
            }
        }
        
        if (has_negative_cycle) break;
    }
    
    return {dist, parent, has_negative_cycle};
}
```

### Time & Space Complexity

```
Time:   O(V * E)  - V relaxations, each checks E edges
Space:  O(V)      - Distance and parent arrays

Much slower than Dijkstra but can handle negatives!
```

### When to Use

```
✓ Shortest path with NEGATIVE weights
✓ DETECT negative cycles
✓ When graph has negative edges
✓ Currency arbitrage detection
✓ Physics simulations

Example:
- Financial markets (profit detection)
- Game physics (gravity, forces)
- Exchange rate cycles
- Constraint satisfaction
```

---

## 4. Floyd-Warshall Algorithm

### What is Floyd-Warshall?

**Floyd-Warshall Algorithm** finds ALL shortest paths:
- Works between EVERY pair of vertices
- O(V³) - slower but complete
- Handles NEGATIVE weights
- Can detect negative cycles

### Visual Example

```
═══════════════════════════════════════════════════════
         FLOYD-WARSHALL PROCESS
═══════════════════════════════════════════════════════

Graph:     0 --3--> 1
           |         |
           |6        |2
           v         v
           2 <------

Initial distances:
      0   1   2
  0 [ 0   3   6 ]
  1 [ ∞   0   2 ]
  2 [ ∞   ∞   0 ]

k=0 (paths through vertex 0):
      0   1   2
  0 [ 0   3   6 ]
  1 [ ∞   0   2 ]
  2 [ ∞   ∞   0 ]
  (No improvement through 0)

k=1 (paths through vertex 1):
      0   1   2
  0 [ 0   3   5 ]  (0→1→2 = 3+2 = 5, better than 6)
  1 [ ∞   0   2 ]
  2 [ ∞   ∞   0 ]

k=2 (paths through vertex 2):
      0   1   2
  0 [ 0   3   5 ]
  1 [ ∞   0   2 ]
  2 [ ∞   ∞   0 ]

Result: All shortest paths found!

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
pair<vector<vector<ll>>, vector<vector<int>>> floyd_warshall() {
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    vector<vector<int>> next_node(n, vector<int>(n, -1));
    
    // Initialize with direct edges
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        next_node[i][i] = i;
        
        for (auto [v, w] : adj[i]) {
            dist[i][v] = w;
            next_node[i][v] = v;
        }
    }
    
    // Try each vertex as intermediate
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                
                // Path through k better than direct?
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k];
                }
            }
        }
    }
    
    return {dist, next_node};
}
```

### Time & Space Complexity

```
Time:   O(V³)     - Three nested loops
Space:  O(V²)     - Distance matrix

Works for small V (< 500)
Negative weights OK
Can detect negative cycles
```

### When to Use

```
✓ ALL pairs shortest paths
✓ Small graphs (V < 500)
✓ Graph with negative weights
✓ Transitive closure
✓ Game strategy optimization

Example:
- Flight price lookup (all cities)
- Game NPC pathfinding
- Network flow analysis
- Physics distance calculations
```

---

## 5. Topological Sort

### What is Topological Sort?

**Topological Sort** orders vertices in a DAG:
- DAG = Directed Acyclic Graph (no cycles)
- Order respects all edges: u before v if u→v exists
- Uses: Kahn's Algorithm (BFS with in-degree)

### Visual Example

```
═══════════════════════════════════════════════════════
          TOPOLOGICAL SORT PROCESS
═══════════════════════════════════════════════════════

DAG:       5 --→ 2 --→ 3
           |           |
           └---→ 0 ←---┘
                 |
                 v
                 1

In-degree: 0:2, 1:1, 2:1, 3:1, 5:0

Kahn's Algorithm:

Step 1: Find all in-degree 0 vertices
        Queue: [5]
        In-deg: [2, 1, 1, 1, 0]

Step 2: Process 5, reduce neighbors
        Remove 5
        Reduce: 2→0, 0→1
        Queue: [2]
        New in-deg 0: 2
        Order: [5]

Step 3: Process 2, reduce neighbors
        Remove 2
        Reduce: 3→0
        Queue: [3]
        New in-deg 0: 3
        Order: [5, 2]

Step 4: Process 3, reduce neighbors
        Remove 3
        Reduce: 1→0
        Queue: [0]
        New in-deg 0: 0, 1
        Order: [5, 2, 3]

Step 5: Process 0, reduce neighbors
        Remove 0
        Reduce: 1→-1
        Queue: [1]
        In-deg 0 now: 1
        Order: [5, 2, 3, 0]

Step 6: Process 1
        Remove 1
        Queue: []
        Order: [5, 2, 3, 0, 1]

Valid Topological Order: 5 → 2 → 3 → 0 → 1

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
vector<int> topological_sort() {
    vector<int> in_degree(n, 0);
    
    // Calculate in-degree for all vertices
    for (int u = 0; u < n; u++) {
        for (auto [v, _] : adj[u]) {
            in_degree[v]++;
        }
    }
    
    // Add all vertices with in-degree 0 to queue
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        
        // Process neighbors, reduce in-degree
        for (auto [v, _] : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // Check if all vertices processed (no cycle)
    return (order.size() == n) ? order : vector<int>();
}
```

### Time & Space Complexity

```
Time:   O(V + E)  - Each vertex and edge once
Space:  O(V)      - In-degree array and queue
```

### When to Use

```
✓ DAG ordering (must be acyclic!)
✓ Dependency resolution
✓ Task scheduling
✓ Prerequisite checking
✓ Compilation order

Example:
- Course prerequisites (what to take first)
- Build systems (compile order)
- Dependency management (npm, pip)
- Task scheduling (what job runs when)
- Recipe steps (cooking order)
```

---

## 6. Kosaraju's SCC

### What is Kosaraju's Algorithm?

**Kosaraju's Algorithm** finds Strongly Connected Components:
- SCC = subset where every vertex reachable from every other
- Uses DFS twice: original graph, then reversed
- O(V + E) time

### Visual Example

```
═══════════════════════════════════════════════════════
        KOSARAJU'S SCC PROCESS
═══════════════════════════════════════════════════════

Graph:     0 → 1 → 2
           ↑   ↓   ↓
           └───3   4

Step 1: DFS on original, record finishing times
        DFS(0): 0 → 1 → 2 → 3
        Finishing order: [3, 2, 1, 0, 4]

Step 2: Reverse graph
        Original: 0→1, 1→2, 2→3, 1→3, 2→4
        Reversed:  1→0, 2→1, 3→2, 3→1, 4→2

Step 3: DFS on reversed in reverse finishing order
        DFS from 0: 0 (SCC1)
        DFS from 4: 4 (SCC2)
        DFS from 1: 1 → 0 (already visited)
        DFS from 2: 2 → 1, 3 → 2, 1 → 0 (SCC3: {1,2,3})

SCCs:
SCC1: {0}
SCC2: {4}
SCC3: {1, 2, 3}

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
vector<vector<int>> kosaraju() {
    // Step 1: DFS on original graph
    vector<int> order;
    vector<int> next_index(n, 0);
    vector<bool> visited(n, false);
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        st.push(i);
        
        while (!st.empty()) {
            int u = st.top();
            
            if (next_index[u] < (int)adj[u].size()) {
                int v = adj[u][next_index[u]++].first;
                if (!visited[v]) {
                    visited[v] = true;
                    st.push(v);
                }
            } else {
                st.pop();
                order.push_back(u);
            }
        }
    }
    
    // Step 2: Build reversed graph
    vector<vector<pair<int, ll>>> rev_adj(n);
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            rev_adj[v].emplace_back(u, w);
        }
    }
    
    // Step 3: DFS on reversed graph in reverse order
    vector<bool> visited2(n, false);
    vector<vector<int>> sccs;
    
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (visited2[u]) continue;
        
        vector<int> comp;
        stack<int> st2;
        st2.push(u);
        visited2[u] = true;
        
        while (!st2.empty()) {
            int node = st2.top();
            st2.pop();
            comp.push_back(node);
            
            for (auto [v, _] : rev_adj[node]) {
                if (!visited2[v]) {
                    visited2[v] = true;
                    st2.push(v);
                }
            }
        }
        
        sccs.push_back(comp);
    }
    
    return sccs;
}
```

### Time & Space Complexity

```
Time:   O(V + E)  - Two DFS passes
Space:  O(V)      - For reversed graph and stacks
```

### When to Use

```
✓ Find Strongly Connected Components
✓ Cycle detection in directed graphs
✓ Social network analysis
✓ Compiler optimization
✓ Website grouping

Example:
- Social networks (find friend groups)
- Web crawling (find page clusters)
- Compiler (optimize code blocks)
- Network analysis (find clusters)
```

---

## 7. Prim's MST

### What is Prim's Algorithm?

**Prim's Algorithm** finds Minimum Spanning Tree:
- MST = tree connecting all vertices with minimum weight
- GREEDY: Always add minimum weight edge to tree
- O((V + E) log V) with priority queue
- For UNDIRECTED graphs only

### Visual Example

```
═══════════════════════════════════════════════════════
           PRIM'S MST PROCESS
═══════════════════════════════════════════════════════

Graph:    0 --1-- 1
          |   4   |
          |       |2
          3 --5-- 2

Start from vertex 0:

Step 1: In MST: {0}
        Edges from 0: (0-1,1), (0-3,3)
        Add minimum: 0-1 weight 1
        
Step 2: In MST: {0, 1}
        Edges from {0,1}: (0-3,3), (1-2,2)
        Add minimum: 1-2 weight 2
        
Step 3: In MST: {0, 1, 2}
        Edges from {0,1,2}: (0-3,3), (2-3,5)
        Add minimum: 0-3 weight 3
        
Step 4: In MST: {0, 1, 2, 3}
        All vertices included!

MST Edges: (0-1,1), (1-2,2), (0-3,3)
Total Weight: 1 + 2 + 3 = 6

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
pair<ll, vector<tuple<int, int, ll>>> prim() {
    vector<ll> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> in_mst(n, false);
    priority_queue<pair<ll, int>,
                   vector<pair<ll, int>>,
                   greater<>> pq;
    
    dist[0] = 0;
    pq.emplace(0, 0);
    ll total = 0;
    vector<tuple<int, int, ll>> mst_edges;
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (in_mst[u]) continue;
        
        in_mst[u] = true;
        total += d;
        
        // Add edge to MST
        if (parent[u] != -1) {
            mst_edges.emplace_back(parent[u], u, d);
        }
        
        // Update neighbors
        for (auto [v, w] : adj[u]) {
            if (!in_mst[v] && w < dist[v]) {
                dist[v] = w;
                parent[v] = u;
                pq.emplace(w, v);
            }
        }
    }
    
    return {total, mst_edges};
}
```

### Time & Space Complexity

```
Time:   O((V + E) log V)  - With priority queue
Space:  O(V)              - Distance and parent arrays
```

### When to Use

```
✓ Minimum Spanning Tree (UNDIRECTED)
✓ Network design (minimum cost)
✓ Cable/road optimization
✓ Cluster analysis
✓ Image segmentation

Example:
- Telephone network (minimum cost to connect cities)
- Road construction (connect cities cheaply)
- Power grid design
- Airline routes (minimum connections)
```

---

## 8. Kruskal's MST

### What is Kruskal's Algorithm?

**Kruskal's Algorithm** finds Minimum Spanning Tree:
- Sorts edges by weight
- Uses Union-Find for cycle detection
- O(E log E) time
- For UNDIRECTED graphs only

### Visual Example

```
═══════════════════════════════════════════════════════
          KRUSKAL'S MST PROCESS
═══════════════════════════════════════════════════════

Graph:    0 --1-- 1
          |   4   |
          |       |2
          3 --5-- 2

Edges sorted: (0-1,1), (1-2,2), (0-3,3), (0-2,4), (2-3,5)

Step 1: Add (0-1,1) → Connect 0,1
        Components: {0,1}, {2}, {3}
        Total: 1

Step 2: Add (1-2,2) → Connect 1,2
        Components: {0,1,2}, {3}
        Total: 3

Step 3: Add (0-3,3) → Connect 0,3
        Components: {0,1,2,3}
        Total: 6

All vertices connected! MST complete.

Skip (0-2,4) - would create cycle
Skip (2-3,5) - would create cycle

MST Edges: (0-1,1), (1-2,2), (0-3,3)
Total: 6

═══════════════════════════════════════════════════════
```

### Algorithm Code

```cpp
pair<ll, vector<tuple<int, int, ll>>> kruskal() {
    // Sort edges by weight
    vector<tuple<ll, int, int>> edges;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            if (u < v) {  // Avoid duplicates
                edges.emplace_back(w, u, v);
            }
        }
    }
    sort(edges.begin(), edges.end());
    
    // Union-Find for cycle detection
    vector<int> parent(n);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;
    
    auto find = [&](int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];  // Path compression
            x = parent[x];
        }
        return x;
    };
    
    auto union_set = [&](int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        
        // Union by rank
        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
        return true;
    };
    
    ll total = 0;
    vector<tuple<int, int, ll>> mst_edges;
    
    for (auto [w, u, v] : edges) {
        if (union_set(u, v)) {
            total += w;
            mst_edges.emplace_back(u, v, w);
            if (mst_edges.size() == n - 1)
                break;
        }
    }
    
    return {total, mst_edges};
}
```

### Time & Space Complexity

```
Time:   O(E log E)     - Sorting edges
Space:  O(V)           - Union-Find arrays
```

### When to Use

```
✓ Minimum Spanning Tree (UNDIRECTED)
✓ Many edges (denser graphs)
✓ Easier to understand and implement
✓ Network design
✓ Cable optimization

Example:
- Network design
- Road construction
- Connection optimization
- Cluster analysis
```

---

## 🔧 Complete Code Explanation

### Class Constructor

```cpp
Graph(int n, bool directed = true) 
    : n(n), directed(directed), edge_count(0) {
    adj.resize(n);
}

// Creates graph with n vertices
// directed = true: directed graph (default)
// directed = false: undirected graph
```

### Adding Edges

```cpp
void add_edge(int u, int v, ll w = 1) {
    adj[u].emplace_back(v, w);      // Add u→v with weight w
    edge_count++;
    
    if (!directed) {
        adj[v].emplace_back(u, w);  // Add v→u if undirected
        edge_count++;
    }
}

// For directed: 0 → 1 weight 5
// graph.add_edge(0, 1, 5);
//
// For undirected: 0 ↔ 1 weight 5
// graph.add_edge(0, 1, 5);
```

### Getting Edge List

```cpp
vector<tuple<int, int, ll>> get_edge_list() const {
    vector<tuple<int, int, ll>> edges;
    
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            if (directed || u < v) {  // Avoid duplicates for undirected
                edges.emplace_back(u, v, w);
            }
        }
    }
    
    return edges;
}

// Returns all edges as list of (from, to, weight)
```

---

## 💻 Usage Examples

### Example 1: BFS & Topological Sort

```cpp
// Unweighted directed graph
Graph g1(4, true);  // 4 vertices, directed
g1.add_edge(0, 1);
g1.add_edge(0, 2);
g1.add_edge(1, 2);
g1.add_edge(2, 3);

// BFS from vertex 0
auto [dist_bfs, parent_bfs] = g1.bfs(0);
cout << "Distances: ";
for (int d : dist_bfs) cout << d << " ";  // 0 1 1 2

// Topological sort
vector<int> topo = g1.topological_sort();
cout << "\nTopological order: ";
for (int v : topo) cout << v << " ";      // 0 1 2 3
```

### Example 2: Dijkstra & Bellman-Ford

```cpp
// Weighted directed graph
Graph g2(4, true);
g2.add_edge(0, 1, 1);
g2.add_edge(0, 2, 4);
g2.add_edge(1, 2, 2);
g2.add_edge(1, 3, 5);
g2.add_edge(2, 3, 1);

// Dijkstra from 0
auto [dist_dijk, parent_dijk] = g2.dijkstra(0);
cout << "Dijkstra distances: ";
for (ll d : dist_dijk) cout << d << " ";  // 0 1 3 4

// Bellman-Ford from 0
auto [dist_bf, parent_bf, has_cycle] = g2.bellman_ford(0);
cout << "\nBellman-Ford distances: ";
for (ll d : dist_bf) cout << d << " ";    // 0 1 3 4
cout << "\nNegative cycle? " << has_cycle; // false
```

### Example 3: Floyd-Warshall

```cpp
// All-pairs shortest paths
Graph g3(3, true);
g3.add_edge(0, 1, 3);
g3.add_edge(1, 2, 2);
g3.add_edge(0, 2, 6);

auto [dist_fw, next] = g3.floyd_warshall();

cout << "All shortest paths:\n";
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (dist_fw[i][j] == Graph::INF)
            cout << "INF ";
        else
            cout << dist_fw[i][j] << " ";
    }
    cout << "\n";
}
// Row 0: 0 3 5
// Row 1: INF 0 2
// Row 2: INF INF 0
```

### Example 4: SCC with Kosaraju

```cpp
// Graph with cycles
Graph g4(5, true);
g4.add_edge(0, 1);
g4.add_edge(1, 2);
g4.add_edge(2, 0);  // Cycle: 0→1→2→0
g4.add_edge(1, 3);
g4.add_edge(3, 4);

auto sccs = g4.kosaraju();

cout << "Strongly Connected Components:\n";
for (int i = 0; i < sccs.size(); i++) {
    cout << "SCC " << i << ": ";
    for (int v : sccs[i]) cout << v << " ";
    cout << "\n";
}
// SCC 0: 0 2 1
// SCC 1: 3
// SCC 2: 4
```

### Example 5: Minimum Spanning Tree

```cpp
// Undirected weighted graph
Graph g5(4, false);  // Undirected
g5.add_edge(0, 1, 1);
g5.add_edge(0, 2, 4);
g5.add_edge(1, 2, 2);
g5.add_edge(1, 3, 5);
g5.add_edge(2, 3, 1);

// Prim's MST
auto [total_prim, mst_prim] = g5.prim();
cout << "Prim's MST (Total: " << total_prim << "):\n";
for (auto [u, v, w] : mst_prim) {
    cout << "  " << u << " -- " << v << " : " << w << "\n";
}

// Kruskal's MST
auto [total_kruskal, mst_kruskal] = g5.kruskal();
cout << "\nKruskal's MST (Total: " << total_kruskal << "):\n";
for (auto [u, v, w] : mst_kruskal) {
    cout << "  " << u << " -- " << v << " : " << w << "\n";
}
// Both give same total weight, different structure
```

---

## 📊 Complexity Analysis

```
╔═══════════════════════════════════════════════════════════════╗
║              ALGORITHM COMPLEXITY COMPARISON                  ║
╠═══════════════════════════════════════════════════════════════╣
║ Algorithm       │ Time          │ Space  │ Best For           ║
╠─────────────────┼───────────────┼────────┼────────────────────╣
║ BFS             │ O(V+E)        │ O(V)   │ Unweighted paths   ║
║ Dijkstra        │ O((V+E)logV)  │ O(V)   │ Weighted paths+    ║
║ Bellman-Ford    │ O(V*E)        │ O(V)   │ Negative weights   ║
║ Floyd-Warshall │ O(V³)         │ O(V²)  │ All pairs (small)  ║
║ Topological     │ O(V+E)        │ O(V)   │ DAG ordering       ║
║ Kosaraju (SCC)  │ O(V+E)        │ O(V)   │ Find components    ║
║ Prim's MST      │ O((V+E)logV)  │ O(V)   │ Dense graphs       ║
║ Kruskal's MST   │ O(ElogE)      │ O(V)   │ General MST        ║
╚═══════════════════════════════════════════════════════════════╝
```

---

## 🎯 When to Use Each Algorithm

```
SHORTEST PATH ALGORITHMS:
├─ Unweighted graph?     → BFS
├─ Weighted + non-negative? → Dijkstra
├─ Negative weights OK?  → Bellman-Ford
└─ All pairs needed?     → Floyd-Warshall

GRAPH STRUCTURE:
├─ Path finding?         → BFS/DFS/Dijkstra
├─ DAG ordering?         → Topological Sort
├─ Find cycles?          → Kosaraju
└─ Find components?      → Kosaraju/BFS

SPANNING TREE:
├─ Undirected weighted?  → Prim or Kruskal
├─ Sparse graph?         → Kruskal (easier)
└─ Dense graph?          → Prim (better)
```

---

## 📈 Performance Tips

```
1. Choose right algorithm:
   - Wrong choice = TLE (Time Limit Exceeded)
   
2. Graph representation matters:
   - Sparse: Adjacency list (used here)
   - Dense: Adjacency matrix
   
3. Optimization techniques:
   - Early termination (if goal found)
   - Pruning (skip impossible paths)
   - Memoization (cache results)
   
4. Constants matter:
   - Use ll for large weights
   - Use fast I/O (sync_with_stdio(false))
   - Avoid string operations in loops
```

---

## 🚀 Installation & Compilation

### Copy Code

```bash
# Copy the entire Graph class to your file
# Include required headers:
#include <bits/stdc++.h>
using namespace std;

// Then paste the Graph class code
```

### Compile

```bash
# With g++
g++ -std=c++17 -O2 graph.cpp -o graph

# With clang
clang++ -std=c++17 -O2 graph.cpp -o graph

# Run
./graph
```

### Include in Other Files

```cpp
#include "graph.h"  // If in separate file

int main() {
    Graph g(5, true);  // Create graph
    g.add_edge(0, 1);
    // ... use algorithms
    return 0;
}
```

---

## 💡 Real-World Applications

```
BFS/DFS:
- Web crawling
- Maze solving
- Social network traversal

Dijkstra:
- GPS navigation (Google Maps)
- Network routing (packets)
- Game pathfinding

Floyd-Warshall:
- Flight price lookup
- Game physics
- Network analysis

Topological Sort:
- Build systems (make, cmake)
- Course prerequisites
- Dependency resolution (npm, pip)

Kosaraju (SCC):
- Website clustering
- Social network groups
- Code optimization

MST (Prim/Kruskal):
- Network design
- Road construction
- Power grid optimization
- Telecommunication networks
```

---

<div align="center">

## ⭐ This Graph Class Includes All You Need!

**BFS • Dijkstra • Bellman-Ford • Floyd-Warshall • Topological Sort • Kosaraju • Prim • Kruskal**

---

### 🏆 Master Graph Algorithms → Master Competitive Programming!

**Production Ready | Professional Quality | Complete Documentation**

[⬆ Back to Top](#-ultimate-graph-class---complete-professional-guide)

</div>
