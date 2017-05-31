/* Relabel-to-front maxflow algorithm - O(V^3) */
struct RelabelToFront {
    vector<int> ptr, h, e;
    FlowGraph &g;    

    RelabelToFront(FlowGraph &g) : g(g) {
        ptr.resize(g.V);
        h.resize(g.V);
        e.resize(g.V);
    }

    int max_flow(int s, int t) {
        fill(ptr.begin(), ptr.end(), 0);
        fill(h.begin(), h.end(), 0);
        fill(e.begin(), e.end(), 0);
        h[s] = g.V;
        forward_list<int> l;
        for (int v = 0; v < g.V; v++)
            if (v != s && v != t)
                l.push_front(v);
        for (int i: g.adj[s]) {
            int nxt = g.edges[i].v;
            if (!g.edges[i].cap) continue;
            e[nxt] += g.edges[i].cap;
            e[s] -= g.edges[i].cap;
            g.edges[i^1].cap = g.edges[i].cap;
            g.edges[i].cap = 0;
        }

        auto curr = l.begin(), last = l.before_begin();
        while (curr != l.end()) {
            int v = *curr;
            bool relabeled = 0;
            while (e[v] > 0) {
                if (ptr[v] == (int)g.adj[v].size()) {
                    h[v]++;
                    ptr[v] = 0;
                    relabeled = 1;
                }
                else {
                    int i = g.adj[v][ptr[v]];
                    int nxt = g.edges[i].v;
                    if (g.edges[i].cap && h[v] == h[nxt] + 1) {
                        int f = min(g.edges[i].cap, e[v]);
                        g.edges[i].cap -= f;
                        g.edges[i^1].cap += f;
                        e[nxt] += f;
                        e[v] -= f;
                    }
                    else ptr[v]++;
                }
            }
            if (relabeled) {
                l.erase_after(last);
                l.push_front(v);
                last = l.before_begin();
                curr = l.begin();
            }
            else {
                last = curr;
                curr++;
            }
        }

        return e[t];
    }
};
