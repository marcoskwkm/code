/* Push-Relabel maxflow algorithm: FIFO rule - O(V^3) */
template<class FTYPE> struct PushRelabelFIFO {
    FlowGraph<FTYPE> &g;

    PushRelabelFIFO(FlowGraph<FTYPE> &_g) : g(_g) {}

    FTYPE max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0);
        vector<FTYPE> e(g.V, 0);
        h[s] = g.V;
        queue<int> q;
        for (int i: g.adj[s]) {
            int w = g.edges[i].v;
            if (!g.edges[i].cap) continue;
            if (!e[w] && w != t) q.push(w);
            e[w] += g.edges[i].cap;
            e[s] -= g.edges[i].cap;
            g.edges[i^1].cap = g.edges[i].cap;
            g.edges[i].cap = 0;
        }

        while (!q.empty()) {
            int v = q.front();
            for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
                int i = g.adj[v][p];
                int w = g.edges[i].v;
                if (h[w] < h[v] && g.edges[i].cap) {
                    FTYPE f = min(g.edges[i].cap, e[v]);
                    g.edges[i].cap -= f;
                    g.edges[i^1].cap += f;
                    if (!e[w] && w != t) q.push(w);
                    e[w] += f;
                    e[v] -= f;
                    if (e[v] == 0) break;
                }
            }
            if (e[v]) {
                ptr[v] = 0;
                h[v]++;
            }
            else q.pop();
        }

        return e[t];
    }
};
