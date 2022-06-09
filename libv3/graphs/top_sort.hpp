template<class EType> vector<int> top_sort(Graph<EType> &g) {
    vector<int> ord;
    vector<int> indeg(g.V, 0);

    for (int u = 0; u < g.V; u++) {
        for (auto edge: g.adj[u]) {
            indeg[edge->v]++;
        }
    }
    for (int v = 0; v < g.V; v++) {
        if (!indeg[v]) {
            ord.push_back(v);
        }
    }
    for (int i = 0; i < (int)ord.size(); i++) {
        int u = ord[i];
        for (auto edge: g.adj[u]) {
            if (!--indeg[edge->v]) {
                ord.push_back(edge->v);
            }
        }
    }

    return ord;
}
