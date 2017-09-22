#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

/* Data structure to represent a network flow graph with costs */
struct CostFlowGraph {
    struct Edge {
        int v;
        int cap;
        int cst;
        Edge(int _v, int _cap, int _cst) : v(_v), cap(_cap), cst(_cst) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    CostFlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, int cap, int cst) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap, cst));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0, -cst));
    }
};

/* 
   Minimum cost maximum flow: Successive Shortest Path implementation
   O(E*V + U*V^2), where U is the maximum flow
*/
struct MinCostMaxFlowSSP {
    CostFlowGraph &g;
    vector<int> d, p;

    MinCostMaxFlowSSP(CostFlowGraph &_g) : g(_g) {
        d.resize(g.V);
        p.resize(g.V);
    }

    void init_p(int s) {
        fill(d.begin(), d.end(), INF);
        d[s] = 0;
        queue<int> q({s});
        vector<bool> queued(g.V, 0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            queued[v] = 0;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v;
                if (!g.edges[i].cap) continue;
                if (d[w] > d[v] + g.edges[i].cst) {
                    d[w] = d[v] + g.edges[i].cst;
                    if (!queued[w]) {
                        q.push(w);
                        queued[w] = 1;
                    }
                }
            }
        }
        for (int v = 0; v < g.V; v++)
            p[v] = d[v];
    }

    pair<int, int> augment(int s, int t) {
        fill(d.begin(), d.end(), INF);
        d[s] = 0;
        vector<bool> done(g.V, 0);
        vector<int> prv(g.V, -1), flow(g.V);
        flow[s] = INF;
        while (1) {
            int v;
            int dist_v = INF;
            for (int w = 0; w < g.V; w++) {
                if (!done[w] && d[w] < dist_v) {
                    v = w;
                    dist_v = d[w];
                }
            }
            if (dist_v == INF) break;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v;
                int cap = g.edges[i].cap, cst = g.edges[i].cst;
                if (cap && d[w] > d[v] + cst + p[v] - p[w]) {
                    d[w] = d[v] + cst + p[v] - p[w];
                    prv[w] = i;
                    flow[w] = min(flow[v], cap);
                }
            }
            done[v] = 1;
        }
        if (d[t] == INF) return make_pair(-1, 0);
        for (int v = 0; v < g.V; v++) p[v] += d[v];

        int flow_cost = 0;
        for (int v = t; v != s; v = g.edges[prv[v]^1].v) {
            g.edges[prv[v]].cap -= flow[t];
            g.edges[prv[v]^1].cap += flow[t];
            flow_cost += flow[t] * g.edges[prv[v]].cst;
        }
        return make_pair(flow[t], flow_cost);
    }

    // Returns a pair (max flow, min cost)
    pair<int, int> mcmf(int s, int t) {
        pair<int, int> ret(0, 0), aug;
        init_p(s);
        while ((aug = augment(s, t)).first != -1) {
            ret.first += aug.first;
            ret.second += aug.second;
        }
        return ret;
    }
};

const int MAXN = 55;
int low[MAXN], hi[MAXN];

int main() {
    int n, q;
    cin >> n >> q;
    fill(low, low + MAXN, 1);
    fill(hi, hi + MAXN, n);
    for (int i = 0; i < q; i++) {
        int k, l, r, v;
        cin >> k >> l >> r >> v;
        if (k == 1) {
            for (int j = l; j <= r; j++)
                low[j] = max(low[j], v);
        }
        else {
            for (int j = l; j <= r; j++)
                hi[j] = min(hi[j], v);
        }
    }

    CostFlowGraph g(n + n + 2);
    int s = 0, t = n + n + 1;

    for (int i = 1; i <= n; i++) {
        for (int q = 1; q <= n; q++) {
            g.add_edge(s, i, 1, 2*q - 1);
        }

        for (int j = 1; j <= n; j++) 
            if (low[j] <= i && i <= hi[j])
                g.add_edge(i, n + j, 1, 0);

        g.add_edge(n + i, t, 1, 0);
    }

    MinCostMaxFlowSSP mcmf(g);

    pii flow = mcmf.mcmf(s, t);

    // for (int j = 1; j <= n; j++) {
    //     for (int idx: g.adj[n + j]) {
    //         if (g.edges[idx].v != t && g.edges[idx].cap > 0) {
    //             printf("%d -> %d\n", g.edges[idx].v, j);
    //         }
    //     }
    // }
    
    if (flow.first < n) printf("-1\n");
    else printf("%d\n", flow.second);
    
    return 0;
}
