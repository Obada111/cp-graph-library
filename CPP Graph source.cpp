#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    using ll = long long;
    const ll INF = 1e18;
    const int NINF = -1e9;

    int n;
    bool directed;
    vector<vector<pair<int, ll>>> adj;
    int edge_count;

    Graph(int n, bool directed = true) : n(n), directed(directed), edge_count(0)
    {
        adj.resize(n);
    }

    void add_edge(int u, int v, ll w = 1)
    {
        adj[u].emplace_back(v, w);
        edge_count++;
        if (!directed)
        {
            adj[v].emplace_back(u, w);
            edge_count++;
        }
    }

    vector<tuple<int, int, ll>> get_edge_list() const
    {
        vector<tuple<int, int, ll>> edges;
        for (int u = 0; u < n; u++)
        {
            for (auto [v, w] : adj[u])
            {
                if (directed || u < v)
                {
                    edges.emplace_back(u, v, w);
                }
            }
        }
        return edges;
    }

    pair<vector<int>, vector<int>> bfs(int s)
    {
        vector<int> dist(n, -1);
        vector<int> parent(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto [v, _] : adj[u])
            {
                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return {dist, parent};
    }

    pair<vector<ll>, vector<int>> dijkstra(int s)
    {
        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            for (auto [v, w] : adj[u])
            {
                ll new_dist = d + w;
                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    parent[v] = u;
                    pq.emplace(new_dist, v);
                }
            }
        }
        return {dist, parent};
    }

    tuple<vector<ll>, vector<int>, bool> bellman_ford(int s)
    {
        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        dist[s] = 0;

        for (int i = 0; i < n - 1; i++)
        {
            bool updated = false;
            for (int u = 0; u < n; u++)
            {
                if (dist[u] == INF)
                    continue;
                for (auto [v, w] : adj[u])
                {
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        updated = true;
                    }
                }
            }
            if (!updated)
                break;
        }

        bool has_negative_cycle = false;
        for (int u = 0; u < n; u++)
        {
            if (dist[u] == INF)
                continue;
            for (auto [v, w] : adj[u])
            {
                if (dist[u] + w < dist[v])
                {
                    has_negative_cycle = true;
                    break;
                }
            }
            if (has_negative_cycle)
                break;
        }

        return {dist, parent, has_negative_cycle};
    }

    pair<vector<vector<ll>>, vector<vector<int>>> floyd_warshall()
    {
        vector<vector<ll>> dist(n, vector<ll>(n, INF));
        vector<vector<int>> next_node(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
            next_node[i][i] = i;
            for (auto [v, w] : adj[i])
            {
                dist[i][v] = w;
                next_node[i][v] = v;
            }
        }

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                if (dist[i][k] == INF)
                    continue;
                for (int j = 0; j < n; j++)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }

        return {dist, next_node};
    }

    vector<int> topological_sort()
    {
        vector<int> in_degree(n, 0);
        for (int u = 0; u < n; u++)
        {
            for (auto [v, _] : adj[u])
            {
                in_degree[v]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] == 0)
            {
                q.push(i);
            }
        }

        vector<int> order;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (auto [v, _] : adj[u])
            {
                if (--in_degree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        return (order.size() == n) ? order : vector<int>();
    }

    vector<vector<int>> kosaraju()
    {
        // First DFS: get finishing order
        vector<int> order;
        vector<int> next_index(n, 0);
        vector<bool> visited(n, false);
        stack<int> st;

        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;
            visited[i] = true;
            st.push(i);
            while (!st.empty())
            {
                int u = st.top();
                if (next_index[u] < (int)adj[u].size())
                {
                    int v = adj[u][next_index[u]++].first;
                    if (!visited[v])
                    {
                        visited[v] = true;
                        st.push(v);
                    }
                }
                else
                {
                    st.pop();
                    order.push_back(u);
                }
            }
        }

        // Build reversed graph
        vector<vector<pair<int, ll>>> rev_adj(n);
        for (int u = 0; u < n; u++)
        {
            for (auto [v, w] : adj[u])
            {
                rev_adj[v].emplace_back(u, w);
            }
        }

        // Second DFS on reversed graph
        vector<bool> visited2(n, false);
        vector<vector<int>> sccs;
        for (int i = (int)order.size() - 1; i >= 0; i--)
        {
            int u = order[i];
            if (visited2[u])
                continue;
            vector<int> comp;
            stack<int> st2;
            st2.push(u);
            visited2[u] = true;
            while (!st2.empty())
            {
                int node = st2.top();
                st2.pop();
                comp.push_back(node);
                for (auto [v, _] : rev_adj[node])
                {
                    if (!visited2[v])
                    {
                        visited2[v] = true;
                        st2.push(v);
                    }
                }
            }
            sccs.push_back(comp);
        }

        return sccs;
    }

    pair<ll, vector<tuple<int, int, ll>>> prim()
    {
        if (directed)
            throw runtime_error("Prim's requires undirected graph");

        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        vector<bool> in_mst(n, false);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        dist[0] = 0;
        pq.emplace(0, 0);
        ll total = 0;
        vector<tuple<int, int, ll>> mst_edges;

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (in_mst[u])
                continue;
            in_mst[u] = true;
            total += d;
            if (parent[u] != -1)
            {
                mst_edges.emplace_back(parent[u], u, d);
            }
            for (auto [v, w] : adj[u])
            {
                if (!in_mst[v] && w < dist[v])
                {
                    dist[v] = w;
                    parent[v] = u;
                    pq.emplace(w, v);
                }
            }
        }

        if (mst_edges.size() != n - 1)
        {
            throw runtime_error("Graph is not connected");
        }

        return {total, mst_edges};
    }

    pair<ll, vector<tuple<int, int, ll>>> kruskal()
    {
        if (directed)
            throw runtime_error("Kruskal's requires undirected graph");

        vector<tuple<ll, int, int>> edges;
        for (int u = 0; u < n; u++)
        {
            for (auto [v, w] : adj[u])
            {
                if (u < v)
                {
                    edges.emplace_back(w, u, v);
                }
            }
        }
        sort(edges.begin(), edges.end());

        vector<int> parent(n);
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        auto find = [&](int x)
        {
            while (x != parent[x])
            {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        auto union_set = [&](int x, int y)
        {
            int rx = find(x), ry = find(y);
            if (rx == ry)
                return false;
            if (rank[rx] < rank[ry])
                parent[rx] = ry;
            else if (rank[rx] > rank[ry])
                parent[ry] = rx;
            else
            {
                parent[ry] = rx;
                rank[rx]++;
            }
            return true;
        };

        ll total = 0;
        vector<tuple<int, int, ll>> mst_edges;
        for (auto [w, u, v] : edges)
        {
            if (union_set(u, v))
            {
                total += w;
                mst_edges.emplace_back(u, v, w);
                if (mst_edges.size() == n - 1)
                    break;
            }
        }

        if (mst_edges.size() != n - 1)
        {
            throw runtime_error("Graph is not connected");
        }

        return {total, mst_edges};
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "========================================\n";
    cout << "GRAPH ALGORITHMS DEMONSTRATION\n";
    cout << "========================================\n\n";

    // Example 1: Unweighted Directed Graph (BFS, Topological Sort)
    cout << "Example 1: Unweighted Directed Graph\n";
    Graph g1(4, true);
    g1.add_edge(0, 1);
    g1.add_edge(0, 2);
    g1.add_edge(1, 2);
    g1.add_edge(2, 3);

    // BFS
    auto [dist_bfs, parent_bfs] = g1.bfs(0);
    cout << "\nBFS from 0:\n";
    cout << "Distances: ";
    for (int d : dist_bfs)
        cout << d << " ";
    cout << "\nParents:   ";
    for (int p : parent_bfs)
        cout << p << " ";

    // Topological Sort
    vector<int> topo = g1.topological_sort();
    cout << "\n\nTopological Order: ";
    if (topo.empty())
        cout << "Not a DAG";
    else
        for (int v : topo)
            cout << v << " ";

    // Example 2: Weighted Directed Graph (Dijkstra, Bellman-Ford)
    cout << "\n\nExample 2: Weighted Directed Graph\n";
    Graph g2(4, true);
    g2.add_edge(0, 1, 1);
    g2.add_edge(0, 2, 4);
    g2.add_edge(1, 2, 2);
    g2.add_edge(1, 3, 5);
    g2.add_edge(2, 3, 1);

    // Dijkstra
    auto [dist_dijk, parent_dijk] = g2.dijkstra(0);
    cout << "\n\nDijkstra from 0:\n";
    cout << "Distances: ";
    for (ll d : dist_dijk)
        cout << d << " ";
    cout << "\nParents:   ";
    for (int p : parent_dijk)
        cout << p << " ";

    // Bellman-Ford
    auto [dist_bf, parent_bf, has_neg_cycle] = g2.bellman_ford(0);
    cout << "\n\nBellman-Ford from 0:\n";
    cout << "Distances: ";
    for (ll d : dist_bf)
        cout << d << " ";
    cout << "\nHas negative cycle? " << (has_neg_cycle ? "Yes" : "No");

    // Example 3: Small Graph for Floyd-Warshall
    cout << "\n\nExample 3: Floyd-Warshall\n";
    Graph g3(3, true);
    g3.add_edge(0, 1, 3);
    g3.add_edge(1, 2, 2);
    g3.add_edge(0, 2, 6);

    auto [dist_fw, next_node] = g3.floyd_warshall();
    cout << "\nAll-Pairs Shortest Paths:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "From " << i << ": ";
        for (ll d : dist_fw[i])
        {
            cout << (d == Graph::INF ? "INF" : to_string(d)) << " ";
        }
        cout << "\n";
    }

    // Example 4: Graph with SCCs (Kosaraju)
    cout << "\nExample 4: Strongly Connected Components\n";
    Graph g4(5, true);
    g4.add_edge(0, 1);
    g4.add_edge(1, 2);
    g4.add_edge(2, 0);
    g4.add_edge(1, 3);
    g4.add_edge(3, 4);

    auto sccs = g4.kosaraju();
    cout << "\nSCCs:\n";
    for (int i = 0; i < (int)sccs.size(); i++)
    {
        cout << "SCC " << i + 1 << ": ";
        for (int v : sccs[i])
            cout << v << " ";
        cout << "\n";
    }

    // Example 5: Undirected Weighted Graph (MST)
    cout << "\nExample 5: Minimum Spanning Tree\n";
    Graph g5(4, false);
    g5.add_edge(0, 1, 1);
    g5.add_edge(0, 2, 4);
    g5.add_edge(1, 2, 2);
    g5.add_edge(1, 3, 5);
    g5.add_edge(2, 3, 1);

    // Prim
    try
    {
        auto [total_prim, mst_prim] = g5.prim();
        cout << "\nPrim's MST (Total: " << total_prim << "):\n";
        for (auto [u, v, w] : mst_prim)
        {
            cout << "  " << u << " -- " << v << " : " << w << "\n";
        }
    }
    catch (const exception &e)
    {
        cout << "Prim: " << e.what() << "\n";
    }

    // Kruskal
    try
    {
        auto [total_kruskal, mst_kruskal] = g5.kruskal();
        cout << "\nKruskal's MST (Total: " << total_kruskal << "):\n";
        for (auto [u, v, w] : mst_kruskal)
        {
            cout << "  " << u << " -- " << v << " : " << w << "\n";
        }
    }
    catch (const exception &e)
    {
        cout << "Kruskal: " << e.what() << "\n";
    }

    return 0;
}