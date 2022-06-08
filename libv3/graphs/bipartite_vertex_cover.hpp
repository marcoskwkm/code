template<class EType> vector<int> find_vertex_cover(Graph<EType> &g, int s, int t) {
    Dinic<EType> dinic(g);
    vector<bool> seen(g.V);
    queue<int> q;

    for (const auto edge: g.adj[s]) {
        if (edge->cap > 0) {
            q.push(edge->v);
            seen[edge->v] = 1;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto edge: g.adj[v]) {
            if (edge->cap == 0 || edge->v == s || edge->v == t || seen[edge->v]) {
                continue;
            }
            seen[edge->v] = 1;
            q.push(edge->v);
        }
    }

    vector<int> cover;
    for (const auto edge: g.adj[s]) {
        if (!seen[edge->v]) {
            cover.push_back(edge->v);
        }
    }
    for (const auto edge: g.adj[t]) {
        if (seen[edge->v]) {
            cover.push_back(edge->v);
        }
    }

    return cover;
}
