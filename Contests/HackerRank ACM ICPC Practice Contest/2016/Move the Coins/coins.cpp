#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e4 + 10;

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

int w[MAXN];
int depth[MAXN];
int dfs_l[MAXN], dfs_r[MAXN];
int dfs_cnt;
int xorsumodd[MAXN], xorsumall[MAXN];
void dfs(int v, int d, int prv, const Graph &g) {
    depth[v] = d;
    dfs_l[v] = dfs_cnt++;
    xorsumall[v] = w[v];
    xorsumodd[v] = (d & 1) ? w[v] : 0;
    for (int nxt: g.adj[v]) {
        if (nxt != prv) {
            dfs(nxt, d + 1, v, g);
            xorsumall[v] ^= xorsumall[nxt];
            xorsumodd[v] ^= xorsumodd[nxt];
        }
    }
    dfs_r[v] = dfs_cnt++;
}

int main() {
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    Graph g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u, v);
        g.add_edge(v, u);
    }
    dfs(1, 0, -1, g);
    for (cin >> q; q--;) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (dfs_l[u] <= dfs_l[v] && dfs_l[v] <= dfs_r[u])
            printf("INVALID\n");
        else if (depth[u] % 2 != depth[v] % 2)
            printf("%s\n", xorsumodd[1] ? "YES" : "NO");
        else
            printf("%s\n", (xorsumodd[1] ^ xorsumall[u]) ? "YES" : "NO");
    }    
    return 0;
}
