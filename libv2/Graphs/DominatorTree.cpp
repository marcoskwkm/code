// O(ElogV) implementation of a dominator tree
struct DominatorTree {
    const Graph &g;

    Graph tree; // The dominator tree
    vector<int> dfs_l, dfs_r;

    // Auxiliary data
    Graph rg;
    vector<vector<int>> bucket;
    vector<int> idom, sdom, prv, pre;
    vector<int> ancestor, label, preorder;

    DominatorTree(const Graph &_g, int s) : g(_g) {
        rg = tree = Graph(g.V);
        idom.resize(g.V), sdom.resize(g.V, -1);
        prv.resize(g.V), pre.resize(g.V, -1), bucket.resize(g.V);
        ancestor.resize(g.V, -1), label.resize(g.V);
        dfs_l.resize(g.V), dfs_r.resize(g.V);
        dfs(s);
        if (preorder.size() == 1) return;
        for (size_t i = preorder.size() - 1; i >= 1; i--) {
            int w = preorder[i];
            for (int v: rg.adj[w]) {
                int u = eval(v);
                if (pre[sdom[u]] < pre[sdom[w]]) sdom[w] = sdom[u];
            }
            bucket[sdom[w]].push_back(w);
            link(prv[w], w);
            for (int v: bucket[prv[w]]) {
                int u = eval(v);
                idom[v] = (u == v) ? sdom[v] : u;
            }
            bucket[prv[w]].clear();
        }
        for (size_t i = 1; i < preorder.size(); i++) {
            int w = preorder[i];
            if (idom[w] != sdom[w]) idom[w] = idom[idom[w]];
            tree.add_edge(idom[w], w);
        }
        idom[s] = sdom[s] = -1;
        dfs2(s);
    }

    void dfs(int v) {
        static int t = 0;
        pre[v] = ++t;
        sdom[v] = label[v] = v;
        preorder.push_back(v);
        for (int nxt: g.adj[v]) {
            if (sdom[nxt] == -1) {
                prv[nxt] = v;
                dfs(nxt);
            }
            rg.add_edge(nxt, v);
        }
    }

    int eval(int v) {
        if (ancestor[v] == -1) return v;
        if (ancestor[ancestor[v]] == -1) return label[v];
        int u = eval(ancestor[v]);
        if (pre[sdom[u]] < pre[sdom[label[v]]]) label[v] = u;
        ancestor[v] = ancestor[u];
        return label[v];
    }

    inline void link(int u, int v) {
        ancestor[v] = u;
    }

    void dfs2(int v) {
        static int t = 0;
        dfs_l[v] = t++;
        for (int nxt: tree.adj[v]) dfs2(nxt);
        dfs_r[v] = t++;
    }

    // Whether every path from s to v passes through u
    inline bool dominates(int u, int v) {
        if (pre[v] == -1) return 1; // vacuously true
        return dfs_l[u] <= dfs_l[v] && dfs_r[v] <= dfs_r[u];
    }        
};
