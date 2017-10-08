// Global mincut - O(VElogV) or O(V^3)
template<class FTYPE> struct StoerWagnerMinCut {
    FlowGraph<FTYPE> g;

    StoerWagnerMinCut(FlowGraph<FTYPE> _g) : g(_g) {}

    FlowGraph<FTYPE> contract(int s, int t) {
        FlowGraph<FTYPE> g2(g.V - 1);
        vector<int> idx(g.V);
        for (int v = 0; v < g.V; v++) idx[v] = v;
        swap(idx[t], idx[g.V - 1]);
        for (int v = 0; v < g.V; v++) {
            if (v == s || v == t) continue;
            int cap = 0;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v, c = g.edges[i].cap;
                if (w == s || w == t) cap += c;
                else if (v < w) g2.add_edge(idx[v], idx[w], c);
            }
            if (cap > 0) g2.add_edge(idx[v], idx[s], cap);
        }
        return g2;
    }

    FTYPE mincut() {
        FTYPE ret = numeric_limits<FTYPE>::max();
        while (g.V > 1) {
            vector<bool> seen(g.V);
            set<pair<FTYPE, int>, greater<pair<FTYPE, int>>> pq({{0, 0}});
            vector<FTYPE> c(g.V);
            int s = -1, t = -1;
            while (!pq.empty()) {
                int v = pq.begin()->second;
                pq.erase(pq.begin());
                seen[v] = 1;
                s = t;
                t = v;
                for (int idx: g.adj[v]) {
                    int w = g.edges[idx].v;
                    if (seen[w]) continue;
                    pq.erase(make_pair(c[w], w));
                    c[w] += g.edges[idx].cap;
                    pq.insert(make_pair(c[w], w));
                }
            }
            ret = min(ret, c[t]);
            g = contract(s, t);
        }
        return ret;
    }
};    
