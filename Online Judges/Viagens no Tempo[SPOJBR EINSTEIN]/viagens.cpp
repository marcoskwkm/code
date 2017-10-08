#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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
        edges.push_back(Edge(u, cap));
    }
};

template<class FTYPE> struct StoerWagnerMinCut {
    FlowGraph<FTYPE> g;

    StoerWagnerMinCut(FlowGraph<FTYPE> _g) : g(_g) {}

    FlowGraph<FTYPE> contract(int s, int t) {
        FlowGraph<FTYPE> g2(g.V - 1);
        vector<int> idx(g.V);
        for (int v = 0; v < g.V; v++) idx[v] = v;
        swap(idx[t], idx[g.V - 1]);
        for (int v = 0; v < g.V; v++) {
            if (v == s || v == t) continue;
            int cap = 0;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v, c = g.edges[i].cap;
                if (w == s || w == t) cap += c;
                else if (v < w) g2.add_edge(idx[v], idx[w], c);
            }
            if (cap > 0) g2.add_edge(idx[v], idx[s], cap);
        }
        return g2;
    }

    FTYPE mincut() {
        FTYPE ret = numeric_limits<FTYPE>::max();
        while (g.V > 1) {
            vector<bool> seen(g.V);
            // set<pair<FTYPE, int>, greater<pair<FTYPE, int>>> pq({{0, 0}});
            vector<FTYPE> c(g.V);
            int s = -1, t = -1;
            // while (!pq.empty()) {
            while (1) {
                int v = -1, d = -1;
                for (int vv = 0; vv < g.V; vv++) {
                    if (!seen[vv] && c[vv] > d) {
                        v = vv;
                        d = c[vv];
                    }
                }
                if (v == -1) break;                        
                // int v = pq.begin()->second;
                // pq.erase(pq.begin());
                seen[v] = 1;
                s = t;
                t = v;
                for (int idx: g.adj[v]) {
                    int w = g.edges[idx].v;
                    if (seen[w]) continue;
                    // pq.erase(make_pair(c[w], w));
                    c[w] += g.edges[idx].cap;
                    // pq.insert(make_pair(c[w], w));
                }
            }
            ret = min(ret, c[t]);
            g = contract(s, t);
        }
        return ret;
    }
};    

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, m;
        cin >> n >> m;
        FlowGraph<int> g(n);
        map<pii, int> edges;
        for (int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            if (u > v) swap(u, v);
            edges[pii(u - 1, v - 1)] = c;
        }
        for (auto p: edges)
            g.add_edge(p.first.first, p.first.second, p.second);
        StoerWagnerMinCut<int> mc(g);
        printf("%d\n", mc.mincut());
    }
    return 0;
}
