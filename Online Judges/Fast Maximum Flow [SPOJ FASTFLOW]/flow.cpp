#include <bits/stdc++.h>
using namespace std;
 
#define debug(args...) fprintf(stderr,args)
 
typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
 
const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
 
/* Data structure to represent a network flow graph */
template<class FTYPE> struct FlowGraph {
    struct Edge {
        int v;
        FTYPE cap;
        Edge(int _v, FTYPE _cap) : v(_v), cap(_cap) {}
    };
 
    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;
 
    FlowGraph(int _V) : V(_V) { adj.resize(V); }
 
    void add_edge(int u, int v, FTYPE cap) {
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
template<class FTYPE> struct PushRelabelFIFOGap {
    FlowGraph<FTYPE> &g;
 
    PushRelabelFIFOGap(FlowGraph<FTYPE> &_g) : g(_g) {}
 
    FTYPE max_flow(int s, int t) {
        vector<int> ptr(g.V, 0), h(g.V, 0), hc(2*g.V, 0);
        vector<FTYPE> e(g.V, 0);
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
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    FlowGraph<lint> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        g.add_edge(u, v, c);
        g.add_edge(v, u, c);
    }
    PushRelabelFIFOGap<lint> mf(g);
    printf("%lld\n", mf.max_flow(1, n));
    return 0;
}
