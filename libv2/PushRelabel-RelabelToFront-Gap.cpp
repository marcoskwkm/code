/* 
   Push-Relabel maxflow algorithm: Relabel-to-front rule - O(V^3) 
   Implements Gap heuristic
*/
struct RelabelToFrontGap {
    FlowGraph &g;    

    RelabelToFrontGap(FlowGraph &_g) : g(_g) {}

    int max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0), nxt(g.V, -1), hc(2*g.V, 0);
        vector<int> e(g.V, 0);
        h[s] = g.V;
        hc[g.V] = 1; hc[0] = g.V - 1;
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
                        int f = min(g.edges[i].cap, e[curr]);
                        g.edges[i].cap -= f;
                        g.edges[i^1].cap += f;
                        e[w] += f;
                        e[curr] -= f;
                        if (!e[curr]) break;
                    }
                }
                if (e[curr]) {
                    int cur_h = h[curr];
                    if (hc[cur_h] == 1 && 0 < cur_h && cur_h < g.V) {
                        for (int u = 0; u < g.V; u++) {
                            if (h[u] >= g.V || h[u] < cur_h) continue;
                            hc[h[u]]--;
                            h[u] = g.V + 1;
                            hc[h[u]]++;
                            ptr[u] = 0;
                        }
                    }
                    else {
                        ptr[curr] = 0;
                        hc[h[curr]]--;
                        h[curr]++;
                        hc[h[curr]]++;
                    }
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
