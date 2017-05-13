/* Sorts vertices in topological order */
struct TopSort {
    vector<int> ord;
    
    const Graph &g;
    vector<int> indeg;

    TopSort(const Graph &_g) : g(_g) {
        indeg.resize(g.V);
        for (int u = 0; u < g.V; u++)
            for (auto v: g.adj[u])
                indeg[v]++;
        for (int v = 0; v < g.V; v++)
            if (!indeg[v])
                ord.push_back(v);
        for (int i = 0; i < (int)ord.size(); i++) {
            int u = ord[i];
            for (auto v: g.adj[u])
                if (!--indeg[v])
                    ord.push_back(v);
        }
    }
};
