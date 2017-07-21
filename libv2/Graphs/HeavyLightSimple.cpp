// Finds heavy paths without building a data structure over them.
struct HeavyLightSimple {
    const Graph &g;
    vector<int> head;   // Head of the heavy path containing i
    vector<int> parent; // Parent of node i

    vector<int> depth, heavy;
    int root;

    HeavyLightSimple(const Graph &_g, int _root) : g(_g), root(_root) {
        head.resize(g.V), parent.resize(g.V), depth.resize(g.V), heavy.resize(g.V, -1);
        parent[root] = -1, depth[root] = 0;
        dfs(root);
        for (int v = 0; v < g.V; v++)
            if (parent[v] == -1 || heavy[parent[v]] != v)
                for (int w = v; w != -1; w = heavy[w])
                    head[w] = v;        
    }

    int dfs(int v) {
        int hi = 0, ret = 1;
        for (int nxt: g.adj[v]) {
            if (nxt == parent[v]) continue;
            parent[nxt] = v;
            depth[nxt] = depth[v] + 1;
            int got = dfs(nxt);
            if (got > hi) {
                hi = got;
                heavy[v] = nxt;
            }
            ret += got;
        }
        return ret;
    }
};
