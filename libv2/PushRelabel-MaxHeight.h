/* Push-Relabel maxflow algorithm: Highest label rule - O(V^2*E^1/2) */
struct PushRelabelMaxHeight {
    FlowGraph &g;

    PushRelabelMaxHeight(FlowGraph &_g) : g(_g) {}

    int max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0), nxt(g.V, -1), hv(2*g.V, -1);
        vector<int> e(g.V, 0);
        h[s] = g.V;
        for (int i: g.adj[s]) {
            int w = g.edges[i].v;
            if (!g.edges[i].cap) continue;
            if (!e[w] && w != t) {
                nxt[w] = hv[0];
                hv[0] = w;
            }
            e[w] += g.edges[i].cap;
            e[s] -= g.edges[i].cap;
            g.edges[i^1].cap = g.edges[i].cap;
            g.edges[i].cap = 0;
        }

        int cur_h = 0;
        while (cur_h >= 0) {
            for (int v = hv[cur_h]; v != -1; v = nxt[v]) {
                for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
                    int i = g.adj[v][p];
                    int w = g.edges[i].v;
                    if (h[w] < h[v] && g.edges[i].cap) {
                        int f = min(g.edges[i].cap, e[v]);
                        g.edges[i].cap -= f;
                        g.edges[i^1].cap += f;
                        if (!e[w] && w != t) {
                            nxt[w] = hv[h[w]];
                            hv[h[w]] = w;
                        }
                        e[w] += f;
                        e[v] -= f;
                        if (e[v] == 0) break;
                    }
                }
                hv[cur_h] = nxt[v];
                if (e[v]) {
                    ptr[v] = 0;
                    h[v]++;
                    nxt[v] = hv[h[v]];
                    hv[h[v]] = v;
                    cur_h++;
                    break;
                }
            }
            if (hv[cur_h] == -1) cur_h--;
        }
        return e[t];
    }
};
