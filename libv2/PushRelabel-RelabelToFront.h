/* Relabel-to-front maxflow algorithm - O(V^3) */
struct RelabelToFront {
    FlowGraph &g;    

    RelabelToFront(FlowGraph &g) : g(g) {}

    int max_flow(int s, int t) {
        vector<int> ptr(g.V, 0);
        vector<int> h(g.V, 0);
        vector<int> e(g.V, 0);
        vector<int> nxt(g.V, -1);
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
            int v = curr;
            bool relabeled = 0;
            while (e[v] > 0) {
                if (ptr[v] == (int)g.adj[v].size()) {
                    h[v]++;
                    ptr[v] = 0;
                    relabeled = 1;
                }
                int i = g.adj[v][ptr[v]];
                int w = g.edges[i].v;
                if (g.edges[i].cap && h[v] == h[w] + 1) {
                    int f = min(g.edges[i].cap, e[v]);
                    g.edges[i].cap -= f;
                    g.edges[i^1].cap += f;
                    e[w] += f;
                    e[v] -= f;
                }
                ptr[v]++;
            }
            if (relabeled) {
                if (last != -1) {
                    nxt[last] = nxt[v];
                    nxt[v] = head;
                    head = v;
                }
                last = -1;
                curr = v;
            }
            else {
                last = curr;
                curr = nxt[curr];
            }
        }

        return e[t];
    }
};
