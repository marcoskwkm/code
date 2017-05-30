/* Generic Push-Relabel maxflow algorithm - O(EV^2) */
struct PushRelabel {
    vector<int> ptr, h, e;
    FlowGraph &g;

    PushRelabel(FlowGraph &g) : g(g) {
        ptr.resize(g.V);
        h.resize(g.V);
        e.resize(g.V);
    }

    int max_flow(int s, int t) {
        fill(ptr.begin(), ptr.end(), 0);
        fill(h.begin(), h.end(), 0);
        fill(e.begin(), e.end(), 0);
        h[s] = g.V;
        queue<int> q;
        for (int i: g.adj[s]) {
            int nxt = g.edges[i].v;
            if (!g.edges[i].cap) continue;
            if (!e[nxt] && nxt != t) q.push(nxt);
            e[nxt] += g.edges[i].cap;
            e[s] -= g.edges[i].cap;
            g.edges[i^1].cap = g.edges[i].cap;
            g.edges[i].cap = 0;
        }

        while (!q.empty()) {
            int v = q.front();
            for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
                int i = g.adj[v][p];
                int nxt = g.edges[i].v;
                if (h[nxt] < h[v] && g.edges[i].cap) {
                    int f = min(g.edges[i].cap, e[v]);
                    g.edges[i].cap -= f;
                    g.edges[i^1].cap += f;
                    if (!e[nxt] && nxt != t) q.push(nxt);
                    e[nxt] += f;
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
