// graph_cp_explained.cpp
// Single-file, readable and efficient Graph utilities for Competitive Programming.
// C++17, compile with: g++ -std=c++17 -O2 graph_cp_explained.cpp -o solution

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename W = long long>
struct Graph {
    // ---------- Types ----------
    struct Edge { int u, v; W w; int id; Edge(int a = 0, int b = 0, W c = 1, int i = -1): u(a), v(b), w(c), id(i) {} };
    int n;
    bool directed;
    vector<vector<pair<int, W>>> adj;  // adjacency list: (to, weight)
    vector<Edge> edges;                // stored edges (useful for BF / listing)

    // ---------- Constructor / reset ----------
    Graph(int nodes = 0, bool isDirected = false) { init(nodes, isDirected); }
    void init(int nodes, bool isDirected = false) {
        n = nodes; directed = isDirected;
        adj.assign(n, {});
        edges.clear();
    }

    // ---------- Add edge ----------
    // 0-indexed. For undirected graphs, we store both directions.
    void addEdge(int u, int v, W w = (W)1, int id = -1) {
        if (u < 0 || u >= n || v < 0 || v >= n) return;
        adj[u].push_back({v, w});
        edges.emplace_back(u, v, w, id);
        if (!directed) {
            adj[v].push_back({u, w});
            // note: edges includes only one directed entry per addEdge; use edgesForMST() when needed
        }
    }

    // ---------- Utility: reconstruct path from parent array ----------
    static vector<int> reconstructPath(const vector<int>& parent, int target) {
        vector<int> path;
        if (target < 0) return path;
        for (int v = target; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }

    // ---------- BFS (unweighted shortest path) ----------
    // returns vector<int> distances ( -1 == unreachable )
    vector<int> breadthFirstSearch(int src) const {
        vector<int> dist(n, -1);
        if (src < 0 || src >= n) return dist;
        queue<int> q;
        dist[src] = 0; q.push(src);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
            }
        }
        return dist;
    }

    // ---------- Multi-source BFS ----------
    vector<int> multiSourceBFS(const vector<int>& sources) const {
        vector<int> dist(n, -1);
        queue<int> q;
        for (int s : sources) if (s >= 0 && s < n && dist[s] == -1) { dist[s] = 0; q.push(s); }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
            }
        }
        return dist;
    }

    // ---------- DFS (recursive order) ----------
    vector<int> depthFirstSearchRecursive(int src) const {
        vector<int> order; vector<char> vis(n, 0);
        function<void(int)> dfs = [&](int u) {
            vis[u] = 1; order.push_back(u);
            for (auto &pr : adj[u]) if (!vis[pr.first]) dfs(pr.first);
        };
        if (src >= 0 && src < n) dfs(src);
        return order;
    }

    // ---------- DFS (iterative) ----------
    vector<int> depthFirstSearchIterative(int src) const {
        vector<int> order; if (src < 0 || src >= n) return order;
        vector<char> vis(n, 0);
        stack<int> st; st.push(src);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (vis[u]) continue;
            vis[u] = 1; order.push_back(u);
            for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                int v = adj[u][i].first;
                if (!vis[v]) st.push(v);
            }
        }
        return order;
    }

    // ---------- Topological sort (Kahn) ----------
    // returns empty vector if cycle detected
    vector<int> topologicalSortKahn() const {
        vector<int> indeg(n, 0);
        for (int u = 0; u < n; ++u) for (auto &pr : adj[u]) indeg[pr.first]++;
        queue<int> q;
        for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (auto &pr : adj[u]) if (--indeg[pr.first] == 0) q.push(pr.first);
        }
        if ((int)topo.size() != n) return {}; // cycle present
        return topo;
    }

    // ---------- Topological sort (DFS-based) ----------
    vector<int> topologicalSortDFS() const {
        vector<int> order; vector<char> vis(n, 0), inStack(n, 0); bool hasCycle = false;
        function<void(int)> dfs = [&](int u) {
            vis[u] = 1; inStack[u] = 1;
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (!vis[v]) dfs(v);
                else if (inStack[v]) hasCycle = true;
            }
            inStack[u] = 0; order.push_back(u);
        };
        for (int i = 0; i < n; ++i) if (!vis[i]) dfs(i);
        if (hasCycle) return {};
        reverse(order.begin(), order.end());
        return order;
    }

    // ---------- Dijkstra (heap). returns {dist, parent} ----------
    pair<vector<W>, vector<int>> dijkstra(int src) const {
        const W INF = numeric_limits<W>::max() / 4;
        vector<W> dist(n, INF);
        vector<int> parent(n, -1);
        if (src < 0 || src >= n) return {dist, parent};
        using P = pair<W, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[src] = 0; pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto &pr : adj[u]) {
                int v = pr.first; W w = pr.second;
                if (w < 0) continue; // negative weights not supported
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        return {dist, parent};
    }

    // ---------- 0-1 BFS (weights 0 or 1) ----------
    vector<W> zeroOneBFS(int src, W INF_VAL = (W)4e18) const {
        vector<W> dist(n, INF_VAL);
        if (src < 0 || src >= n) return dist;
        deque<int> dq; dist[src] = 0; dq.push_front(src);
        while (!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            for (auto &pr : adj[u]) {
                int v = pr.first; W w = pr.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    if (w == 0) dq.push_front(v); else dq.push_back(v);
                }
            }
        }
        return dist;
    }

    // ---------- Bellman-Ford: returns (dist, hasNegativeCycle, parent) ----------
    tuple<vector<W>, bool, vector<int>> bellmanFord(int src) const {
        const W INF = numeric_limits<W>::max() / 4;
        vector<W> dist(n, INF); vector<int> parent(n, -1);
        if (src < 0 || src >= n) return {dist, false, parent};
        // build unique edge list (for undirected use u<v)
        vector<Edge> E;
        if (directed) E = edges;
        else {
            set<pair<pair<int, int>, W>> s;
            for (int u = 0; u < n; ++u) for (auto &pr : adj[u]) {
                    int v = pr.first; W w = pr.second;
                    if (u < v) s.insert({{u, v}, w});
                }
            for (auto &it : s) E.emplace_back(it.first.first, it.first.second, it.second);
        }
        dist[src] = 0;
        for (int i = 0; i < n - 1; ++i) {
            bool any = false;
            for (auto &e : E) {
                if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
                    dist[e.v] = dist[e.u] + e.w;
                    parent[e.v] = e.u;
                    any = true;
                }
            }
            if (!any) break;
        }
        bool negCycle = false;
        for (auto &e : E) if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) { negCycle = true; break; }
        return {dist, negCycle, parent};
    }

    // ---------- Shortest path on DAG ----------
    vector<W> shortestPathOnDAG(int src, W INF_VAL = numeric_limits<W>::max() / 4) const {
        auto topo = topologicalSortDFS();
        if (topo.empty()) return {}; // not DAG or cycle
        vector<W> dist(n, INF_VAL); dist[src] = 0;
        for (int u : topo) {
            if (dist[u] == INF_VAL) continue;
            for (auto &pr : adj[u]) {
                int v = pr.first; W w = pr.second;
                if (dist[v] > dist[u] + w) dist[v] = dist[u] + w;
            }
        }
        return dist;
    }

    // ---------- DSU for MST (Kruskal) ----------
    struct DSU {
        vector<int> p, r;
        DSU(int n = 0) { init(n); }
        void init(int n) { p.resize(n); r.assign(n, 0); for (int i = 0; i < n; ++i) p[i] = i; }
        int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
        bool unite(int a, int b) {
            a = find(a); b = find(b); if (a == b) return false;
            if (r[a] < r[b]) swap(a, b);
            p[b] = a; if (r[a] == r[b]) r[a]++; return true;
        }
    };

    // return unique undirected edges (u < v)
    vector<Edge> edgesForMST() const {
        set<pair<pair<int, int>, W>> s;
        for (int u = 0; u < n; ++u) for (auto &pr : adj[u]) {
                int v = pr.first; W w = pr.second;
                if (u < v) s.insert({{u, v}, w});
            }
        vector<Edge> out; out.reserve(s.size());
        for (auto &it : s) out.emplace_back(it.first.first, it.first.second, it.second);
        return out;
    }

    // ---------- Kruskal MST (undirected) ----------
    pair<W, vector<Edge>> kruskalMST() const {
        if (directed) return {0, {}};
        auto uniq = edgesForMST();
        sort(uniq.begin(), uniq.end(), [](const Edge & a, const Edge & b) { return a.w < b.w; });
        DSU dsu(n); vector<Edge> used; W total = 0;
        for (auto &e : uniq) if (dsu.unite(e.u, e.v)) { used.push_back(e); total += e.w; }
        return {total, used};
    }

    // ---------- Prim MST ----------
    pair<W, vector<int>> primMST(int src = 0) const {
        const W INF = numeric_limits<W>::max() / 4;
        vector<W> key(n, INF); vector<int> parent(n, -1); vector<char> inMST(n, 0);
        using P = pair<W, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        key[src] = 0; pq.push({0, src});
        while (!pq.empty()) {
            auto [k, u] = pq.top(); pq.pop();
            if (inMST[u]) continue;
            inMST[u] = 1;
            for (auto &pr : adj[u]) {
                int v = pr.first; W w = pr.second;
                if (!inMST[v] && w < key[v]) { key[v] = w; parent[v] = u; pq.push({key[v], v}); }
            }
        }
        W total = 0;
        for (int i = 0; i < n; ++i) if (parent[i] != -1) total += key[i];
        return {total, parent};
    }

    // ---------- Strongly Connected Components (Kosaraju) ----------
    vector<vector<int>> kosarajuSCC() const {
        vector<char> vis(n, 0); vector<int> order;
        function<void(int)> dfs1 = [&](int u) { vis[u] = 1; for (auto &pr : adj[u]) if (!vis[pr.first]) dfs1(pr.first); order.push_back(u); };
        for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);
        vector<vector<int>> radj(n);
        for (int u = 0; u < n; ++u) for (auto &pr : adj[u]) radj[pr.first].push_back(u);
        vis.assign(n, 0);
        vector<vector<int>> comps;
        function<void(int, vector<int>&)> dfs2 = [&](int u, vector<int>& comp) { vis[u] = 1; comp.push_back(u); for (int v : radj[u]) if (!vis[v]) dfs2(v, comp); };
        for (int i = (int)order.size() - 1; i >= 0; --i) if (!vis[order[i]]) { vector<int> comp; dfs2(order[i], comp); comps.push_back(comp); }
        return comps;
    }

    // ---------- Tarjan SCC ----------
    vector<vector<int>> tarjanSCC() const {
        vector<int> disc(n, -1), low(n, -1), st; vector<char> inSt(n, 0);
        int time = 0; vector<vector<int>> comps;
        function<void(int)> dfs = [&](int u) {
            disc[u] = low[u] = time++; st.push_back(u); inSt[u] = 1;
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (disc[v] == -1) { dfs(v); low[u] = min(low[u], low[v]); }
                else if (inSt[v]) low[u] = min(low[u], disc[v]);
            }
            if (low[u] == disc[u]) {
                vector<int> comp;
                while (!st.empty()) { int w = st.back(); st.pop_back(); inSt[w] = 0; comp.push_back(w); if (w == u) break; }
                comps.push_back(comp);
            }
        };
        for (int i = 0; i < n; ++i) if (disc[i] == -1) dfs(i);
        return comps;
    }

    // ---------- Bridges and Articulation Points ----------
    pair<vector<pair<int, int>>, vector<int>> findBridgesAndArticulationPoints() const {
        vector<int> tin(n, -1), low(n, -1), parent(n, -1);
        vector<char> visited(n, 0), isArt(n, 0);
        int timer = 0; vector<pair<int, int>> bridges;
        function<void(int)> dfs = [&](int u) {
            visited[u] = 1; tin[u] = low[u] = timer++; int children = 0;
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (v == parent[u]) continue;
                if (visited[v]) low[u] = min(low[u], tin[v]);
                else {
                    parent[v] = u; children++; dfs(v); low[u] = min(low[u], low[v]);
                    if (low[v] > tin[u]) bridges.emplace_back(u, v);
                    if (parent[u] != -1 && low[v] >= tin[u]) isArt[u] = 1;
                }
            }
            if (parent[u] == -1 && children > 1) isArt[u] = 1;
        };
        for (int i = 0; i < n; ++i) if (!visited[i]) dfs(i);
        vector<int> arts; for (int i = 0; i < n; ++i) if (isArt[i]) arts.push_back(i);
        return {bridges, arts};
    }

    // ---------- LCA (Binary Lifting) for trees ----------
    struct LCA {
        int N = 0, LOG = 0; vector<int> depth; vector<vector<int>> up; bool ready = false;
        void init(int nodes) {
            N = nodes; LOG = 1;
            while ((1 << LOG) <= N) ++LOG;
            depth.assign(N, 0); up.assign(LOG, vector<int>(N, -1)); ready = false;
        }
        void buildFromTreeAdj(const vector<vector<int>>& tree, int root = 0) {
            init((int)tree.size());
            function<void(int, int)> dfs = [&](int u, int p) {
                up[0][u] = p;
                for (int v : tree[u]) if (v != p) { depth[v] = depth[u] + 1; dfs(v, u); }
            };
            depth[root] = 0; dfs(root, -1);
            for (int k = 1; k < LOG; ++k) for (int v = 0; v < N; ++v) up[k][v] = (up[k - 1][v] == -1) ? -1 : up[k - 1][ up[k - 1][v] ];
            ready = true;
        }
        int query(int a, int b) const {
            if (!ready) return -1;
            if (depth[a] < depth[b]) swap((int&)a, (int&)b);
            int diff = depth[a] - depth[b];
            for (int k = 0; k < LOG; ++k) if (diff & (1 << k)) a = up[k][a];
            if (a == b) return a;
            for (int k = LOG - 1; k >= 0; --k) if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
            return up[0][a];
        }
        int kthAncestor(int v, int k) const {
            if (!ready) return -1;
            for (int i = 0; i < LOG && v != -1; ++i) if (k & (1 << i)) v = up[i][v];
            return v;
        }
    };

    // ---------- Dinic (maxflow) ----------
    struct Dinic {
        struct E { int to; ll cap; int rev; };
        int N; vector<vector<E>> G; vector<int> level, it;
        Dinic(int n = 0) { reset(n); }
        void reset(int n) { N = n; G.assign(n, {}); level.assign(n, -1); it.assign(n, 0); }
        void addEdge(int u, int v, ll cap) { G[u].push_back({v, cap, (int)G[v].size()}); G[v].push_back({u, 0, (int)G[u].size() - 1}); }
        bool bfs(int s, int t) {
            fill(level.begin(), level.end(), -1); queue<int> q; level[s] = 0; q.push(s);
            while (!q.empty()) { int v = q.front(); q.pop(); for (auto &e : G[v]) if (e.cap > 0 && level[e.to] == -1) { level[e.to] = level[v] + 1; q.push(e.to); } }
            return level[t] != -1;
        }
        ll dfs(int v, int t, ll f) {
            if (!f) return 0; if (v == t) return f;
            for (int &i = it[v]; i < (int)G[v].size(); ++i) {
                auto &e = G[v][i];
                if (e.cap > 0 && level[e.to] == level[v] + 1) {
                    ll got = dfs(e.to, t, min(f, e.cap));
                    if (got > 0) { e.cap -= got; G[e.to][e.rev].cap += got; return got; }
                }
            }
            return 0;
        }
        ll maxflow(int s, int t) {
            ll flow = 0;
            while (bfs(s, t)) { fill(it.begin(), it.end(), 0); while (true) { ll f = dfs(s, t, numeric_limits<ll>::max()); if (!f) break; flow += f; } }
            return flow;
        }
    };
};

// -------------------- Minimal usage examples --------------------
/*
Example 1: Dijkstra + path
Graph<ll> G(n, false);
for each edge (u,v,w): G.addEdge(u,v,w);
auto [dist, parent] = G.dijkstra(src);
if (dist[t] >= INF) print "INF"; else path = Graph<ll>::reconstructPath(parent, t);

Example 2: Kruskal MST
auto [totalW, usedEdges] = G.kruskalMST();

Example 3: Dinic maxflow
Graph<ll>::Dinic mf(nodeCount);
mf.addEdge(u,v,capacity);
ll flow = mf.maxflow(s,t);

Example 4: LCA on tree
vector<vector<int>> tree(n);
build tree adjacency (0-indexed);
Graph<ll>::LCA lca;
lca.buildFromTreeAdj(tree, root);
int a = lca.query(u,v);

Important notes:
- Nodes are 0-indexed. Convert input if needed.
- Use long long (Graph<long long>) when weights/sums are large.
- Compile with -O2 for contest use.
*/
