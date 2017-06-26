#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30, MAXL = 32;
const int MAXV = 2*MAXN*MAXL + 2;
const int INF = 0x3f3f3f3f;

/* Data structure to represent a network flow graph */
struct FlowGraph {
    struct Edge {
        int v, cap;
        Edge(int _v, int _cap) : v(_v), cap(_cap) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    FlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, int cap) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0));
    }
};

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

struct square {
    int x, y, p;
    square(int a, int b, int c) { x = a; y = b; p = c; }
    square(){}
} ward[MAXL*MAXN + 10];

bool intersect(int a, int b) {
    return max(abs(ward[a].x - ward[b].x), abs(ward[a].y - ward[b].y)) <=
        ward[a].p*ward[a].p + ward[b].p*ward[b].p;
}

int main() {
    int w, n;
    while (scanf("%d%d", &w, &n) && w) {
        int beg = 0;
        int q = 0;
        for (int a = 0; a < n; ++a) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            beg += z;
            int p = 1;
            while (max(x, w - x) >= p*p) {
                ward[q++] = square(x, y, p++);
            }
        }
        FlowGraph g(2*q + 2);
        for (int a = 0; a < q; ++a) {
            if (ward[a].p * ward[a].p >= ward[a].x)
                g.add_edge(0, 2*a + 2, INF);
            if (ward[a].p * ward[a].p >= w - ward[a].x)
                g.add_edge(2*a + 3, 1, INF);
            g.add_edge(2*a + 2, 2*a + 3, 1);
        }
        for (int a = 0; a < q; ++a) {
            for (int b = a + 1; b < q; ++b) {
                if (intersect(a, b)) {
                    g.add_edge(2*a + 3, 2*b + 2, INF);
                    g.add_edge(2*b + 3, 2*a + 2, INF);
                }
            }
        }
        PushRelabelFIFOGap mf(g);
        int end = q - mf.max_flow(0,1);
        printf("%d\n", max(0, beg - end));
    }
    return 0;
}
