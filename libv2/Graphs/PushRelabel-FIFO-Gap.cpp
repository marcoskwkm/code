/* 
   Push-Relabel maxflow algorithm: FIFO rule - O(V^3) 
   Implements Gap heuristic.
*/
struct PushRelabelFIFOGap {
    FlowGraph &g;

    PushRelabelFIFOGap(FlowGraph &_g) : g(_g) {}

    int max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0), hc(2*g.V, 0);
        vector<int> e(g.V, 0);
        h[s] = g.V;
        hc[g.V] = 1; hc[0] = g.V - 1;
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
                    int f = min(g.edges[i].cap, e[v]);
                    g.edges[i].cap -= f;
                    g.edges[i^1].cap += f;
                    if (!e[w] && w != t) q.push(w);
                    e[w] += f;
                    e[v] -= f;
                    if (e[v] == 0) break;
                }
            }
            if (e[v]) {
                int cur_h = h[v];
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
                    ptr[v] = 0;
                    hc[h[v]]--;
                    h[v]++;
                    hc[h[v]]++;
                }
            }
            else q.pop();
        }

        return e[t];
    }
};
