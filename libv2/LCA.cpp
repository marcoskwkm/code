struct LCA {
    static const int LOG = 20;
    vector<int> up[LOG];
    vector<int> depth;

    const Graph &g;

    LCA(const Graph &_g, int root) : g(_g) {
        for (int i = 0; i < LOG; i++)
            up[i].resize(g.V);
        depth.resize(g.V);
        dfs(root, root, 0);
        for (int e = 1; e < LOG; e++)
            for (int v = 0; v < g.V; v++)
                up[e][v] = up[e - 1][up[e - 1][v]];
    }

    void dfs(int v, int prv, int d) {
        depth[v] = d;
        up[0][v] = prv;
        for (int nxt: g.adj[v])
            if (nxt != prv)
                dfs(nxt, v, d + 1);
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
            if (depth[up[i][v]] > depth[u])
                v = up[i][v];
        if (depth[v] > depth[u]) v = up[0][v];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--)
            if (up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        return up[0][v];
    }
};    
