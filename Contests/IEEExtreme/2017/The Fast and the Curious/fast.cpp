#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

struct BridgeAP {
    vector<int> ind, low;
    const Graph &g;

    set<pii> bridges;
    vector<bool> aps;

    BridgeAP(const Graph &_g) : g(_g) {
        ind.resize(g.V, -1);
        low.resize(g.V);
        aps.resize(g.V);
        for (int v = 0; v < g.V; v++)
            if (ind[v] == -1)
                dfs(v, -1);
    }

    void dfs(int v, int prv) {
        static int cnt = 0;
        ind[v] = low[v] = cnt++;
        int q = 0;
        bool flag = 0;
        for (int nxt: g.adj[v]) {
            if (ind[nxt] == -1) {
                ++q;
                dfs(nxt, v);
                low[v] = min(low[v], low[nxt]);
                if (low[nxt] >= ind[v]) flag = 1;
                if (low[nxt] == ind[nxt]) {
                    pii bridge(v, nxt);
                    if (v > nxt) swap(bridge.first, bridge.second);
                    bridges.insert(bridge);
                }
            }
            else if (nxt != prv) low[v] = min(low[v], ind[nxt]);
        }
        if (prv == -1) {
            if (q > 1) aps[v] = 1;
        }
        else if (flag) aps[v] = 1;
    }

    bool is_bridge(int u, int v) const {
        if (u > v) swap(u, v);
        return bridges.find(pii(u, v)) != bridges.end();
    }

    bool is_ap(int v) const { return aps[v]; }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u - 1, v - 1);
    }
    BridgeAP bap(g);
    for (int v = 0; v < n; v++) {
        bool ok = 1;
        for (int nxt: g.adj[v])
            if (!bap.is_bridge(v, nxt))
                ok = 0;
        if (ok) printf("%d\n", v + 1);
    }        
    return 0;
}
