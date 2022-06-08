// Finds a minimum vertex cover of a bipartite graph
// g must be built such that all edges are oriented from s to t with capacity 1
// Note: The complement of the cover provided is a maximum independent set
//
// Depends on FlowGraph and Dinic

vector<int> find_vertex_cover(FlowGraph<int> &g, int s, int t) {
    Dinic<int> dinic(g);
    vector<bool> seen(g.V);
    queue<int> q;
    dinic.max_flow(s, t);

    for (int idx: g.adj[s]) {
        if (g.edges[idx].cap > 0) {
            q.push(g.edges[idx].v);
            seen[g.edges[idx].v] = 1;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int idx: g.adj[v]) {
            int nxt = g.edges[idx].v;
            if (g.edges[idx].cap == 0 || nxt == s || nxt == t || seen[nxt]) {
                continue;
            }
            seen[nxt] = 1;
            q.push(nxt);
        }
    }

    vector<int> cover;
    for (int idx: g.adj[s]) {
        if (!seen[g.edges[idx].v]) {
            cover.push_back(g.edges[idx].v);
        }
    }
    for (int idx: g.adj[t]) {
        if (seen[g.edges[idx].v]) {
            cover.push_back(g.edges[idx].v);
        }
    }

    return cover;
}
