/* Push-Relabel maxflow algorithm: Relabel-to-front rule - O(V^3) */
template<class FTYPE> struct RelabelToFront {
    FlowGraph<FTYPE> &g;    

    RelabelToFront(FlowGraph<FTYPE> &_g) : g(_g) {}

    FTYPE max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0), nxt(g.V, -1);
        vector<FTYPE> e(g.V, 0);
        h[s] = g.V;
        int curr = -1;
        for (int v = 0; v < g.V; v++) {
            if (v != s && v != t) {
                nxt[v] = curr;
                curr = v;
            }
        }
        for (int i: g.adj[s]) {
            int w = g.edges[i].v;
            if (!g.edges[i].cap) continue;
            e[w] += g.edges[i].cap;
            e[s] -= g.edges[i].cap;
            g.edges[i^1].cap = g.edges[i].cap;
            g.edges[i].cap = 0;
        }

        int head = curr, last = -1;
        while (curr != -1) {
            if (e[curr]) {
                for (int &p = ptr[curr]; p < (int)g.adj[curr].size(); p++) {
                    int i = g.adj[curr][p];
                    int w = g.edges[i].v;
                    if (h[w] < h[curr] && g.edges[i].cap) {
                        FTYPE f = min(g.edges[i].cap, e[curr]);
                        g.edges[i].cap -= f;
                        g.edges[i^1].cap += f;
                        e[w] += f;
                        e[curr] -= f;
                        if (!e[curr]) break;
                    }
                }
                if (e[curr]) {
                    ptr[curr] = 0;
                    h[curr]++;
                    if (last != -1) {
                        nxt[last] = nxt[curr];
                        nxt[curr] = head;
                        last = -1;
                        head = curr;
                    }
                    continue;
                }
            }
            last = curr;
            curr = nxt[curr];
        }

        return e[t];
    }
};
