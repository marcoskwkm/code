// DataStructure must implement:
//   Empty constructor
//   init(vector with initial values)
//   query(l, r)
//   update(pos, val) or update(l, r, val)
template<class DataStructure> struct HeavyLight {
    DataStructure tree;
    vector<int> heavy, parent, depth, value, root, pos;
    int n;

    int dfs(const WeightedGraph<int> &g, int v) {
        int hi = 0, ret = 1;
        for (pii edge: g.adj[v]) {
            int nxt, cst;
            tie(nxt, cst) = edge;
            if (nxt == parent[v]) continue;
            parent[nxt] = v;
            value[nxt] = cst;
            depth[nxt] = depth[v] + 1;
            int got = dfs(g, nxt);
            if (got > hi) {
                hi = got;
                heavy[v] = nxt;
            }
            ret += got;
        }
        return ret;
    }

    HeavyLight(const WeightedGraph<int> &g, int s) : n(g.V) {
        heavy = vector<int>(n, -1);
        parent = depth = value = root = pos = vector<int>(n);
        parent[s] = -1;
        dfs(g, s);
        vector<int> tree_val(n);
        int cur = 0;
        for (int v = 0; v < n; v++) {
            if (parent[v] == -1 || heavy[parent[v]] != v) {
                for (int j = v; j != -1; j = heavy[j]) {
                    root[j] = v, pos[j] = cur++;
                    tree_val[pos[j]] = value[j];
                }
            }
        }
        tree.init(tree_val);
    }

    lint query(int u, int v) {
        lint ret = 0;
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (u == -1 || v == -1) abort();
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            ret += tree.query(pos[root[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (u != v) ret += tree.query(pos[u] + 1, pos[v]);
        return ret;
    }

    // Single update
    void update(int v, int val) { tree.update(pos[v], val); }

    // Range update
    void update(int u, int v, int val) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (u == -1 || v == -1) abort();
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            tree.update(pos[root[v]], pos[v], val);
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (u != v) tree.update(pos[u] + 1, pos[v], val);
    }
};
