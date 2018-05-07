#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> Edge;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MAXM = (int)2e5 + 10;

struct UnionFind {
    int n;
    vector<int> prv, rnk;

    UnionFind(int _n) {
        n = _n;
        prv.resize(n, 0);
        rnk.resize(n, 0);
        for (int i = 0; i < n; i++)
            prv[i] = i;
    }

    int find(int v) { return prv[v] = (prv[v] == v) ? v : find(prv[v]); }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rnk[u] > rnk[v]) prv[v] = u;
        else if (rnk[u] < rnk[v]) prv[u] = v;
        else {
            prv[v] = u;
            rnk[u]++;
        }
    }
};

struct Graph {
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> idx;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
        idx.resize(V);
    }

    void add_edge(int u, int v, int i) {
        adj[u].push_back(v);
        idx[u].push_back(i);
    }
};

struct LCA {
    static const int LOG = 20;
    vector<int> up[LOG];
    vector<int> depth;

    const Graph &g;

    LCA(const Graph &_g, int root) : g(_g) {
        for (int i = 0; i < LOG; i++)
            up[i].resize(g.V);
        depth.resize(g.V);
        dfs(root, root, 0);
        for (int e = 1; e < LOG; e++)
            for (int v = 0; v < g.V; v++)
                up[e][v] = up[e - 1][up[e - 1][v]];
    }

    void dfs(int v, int prv, int d) {
        depth[v] = d;
        up[0][v] = prv;
        for (int nxt: g.adj[v])
            if (nxt != prv)
                dfs(nxt, v, d + 1);
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
            if (depth[up[i][v]] > depth[u])
                v = up[i][v];
        if (depth[v] > depth[u]) v = up[0][v];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--)
            if (up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        return up[0][v];
    }
};    


int nxtfree[MAXN];
int edgev[MAXM];
int cost[MAXM];
int delta[MAXM];
bool seen[MAXM];

void dfs(int v, int prv, const Graph &g) {    
    nxtfree[v] = v;
    for (int i = 0; i < (int)g.adj[v].size(); i++) {
        int nxt = g.adj[v][i], idx = g.idx[v][i];
        if (nxt == prv) continue;
        edgev[nxt] = idx;
        dfs(nxt, v, g);
    }
}

int find(int u) { return nxtfree[u] = (nxtfree[u] == u) ? u : find(nxtfree[u]); }

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            edges.push_back(Edge(c, u - 1, v - 1, i));
            delta[i] = 0;
            seen[i] = 0;
        }
        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        vector<Edge> rem;
        lint opt = 0;
        Graph g(n);
        for (Edge edge: edges) {
            int u, v, c, i;
            tie(c, u, v, i) = edge;
            if (uf.find(u) == uf.find(v)) rem.push_back(edge);
            else {
                opt += c;
                cost[i] = c;
                uf.join(u, v);
                g.add_edge(u, v, i);
                g.add_edge(v, u, i);
            }
        }

        bool connected = 1;
        for (int v = 1; v < n; v++) {
            if (uf.find(v) != uf.find(0)) {
                connected = 0;
                break;
            }
        }
        if (!connected) {
            for (int i = 0; i < m; i++)
                printf("-1\n");
            continue;
        }
        
        dfs(0, 0, g);
        LCA lca(g, 0);
        for (Edge edge: rem) {
            int u, v, c, i;
            tie(c, u, v, i) = edge;
            seen[i] = 1;
            int w = lca.lca(u, v);
            while (1) {
                u = find(u);
                if (lca.depth[u] <= lca.depth[w]) break;
                int idx = edgev[u];
                delta[idx] = c - cost[idx];
                seen[idx] = 1;
                nxtfree[u] = nxtfree[lca.up[0][u]];
            }
            while (1) {
                v = find(v);
                if (lca.depth[v] <= lca.depth[w]) break;
                int idx = edgev[v];
                delta[idx] = c - cost[idx];
                seen[idx] = 1;
                nxtfree[v] = nxtfree[lca.up[0][v]];
            }
        }

        for (int i = 0; i < m; i++) {
            if (!seen[i]) printf("-1\n");
            else printf("%lld\n", opt + delta[i]);
        }
    }        
    return 0;
}
