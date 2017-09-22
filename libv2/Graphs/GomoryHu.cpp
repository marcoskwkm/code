/* 
   Computes a Gomory-Hu tree of a given undirected graph.
   Any minimum cut (S, T) in the tree is also a minimum cut in the original
   graph.   
*/
template<class FTYPE, template<class> class MF>
WeightedGraph<FTYPE> GomoryHuTree(const FlowGraph<FTYPE> &g) {
    vector<int> parent(g.V, 0), depth(g.V, 0);
    vector<FTYPE> cap(g.V);
    for (int s = 1; s < g.V; s++) {
        int t = parent[s];
        FlowGraph<FTYPE> g2 = g;
        MF<FTYPE> mf(g2);
        int fst = mf.max_flow(s, t);
        cap[s] = fst;
        vector<bool> in_cut(g.V, 0);
        queue<int> q({s});
        in_cut[s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i: g2.adj[v]) {
                int nxt = g2.edges[i].v;
                if (g2.edges[i].cap > 0 && !in_cut[nxt]) {
                    in_cut[nxt] = 1;
                    q.push(nxt);
                }
            }
        }
        for (int v = 0; v < g.V; v++)
            if (v != s && in_cut[v] && parent[v] == t)
                parent[v] = s;
        if (in_cut[parent[t]]) {
            parent[s] = parent[t];
            parent[t] = s;
            cap[s] = cap[t];
            cap[t] = fst;
        }
    }
    WeightedGraph<FTYPE> tree(g.V);
    for (int v = 1; v < g.V; v++) {
        tree.add_edge(v, parent[v], cap[v]);
        tree.add_edge(parent[v], v, cap[v]);
    }
    return tree;
};
