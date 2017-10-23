#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 3010;

int dist[MAXN][MAXN];
bool reaches[MAXN][MAXN];

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

void dfs(const Graph &g, int s, int v) {
    reaches[s][v] = 1;
    for (int nxt: g.adj[v])
        if (!reaches[s][nxt])
            dfs(g, s, nxt);
}

int get_dist(const Graph &g, int v, int t) {
    if (v == t) return dist[v][t] = 0;
    dist[v][t] = -2;
    for (int nxt: g.adj[v]) {
        if (!reaches[nxt][t]) continue;
        if (dist[nxt][t] == -2)
            return dist[v][t] = INF;
        if (dist[nxt][t] == -1)
            get_dist(g, nxt, t);
        return dist[v][t] = (dist[nxt][t] == INF ? INF : dist[nxt][t] + 1);
    }
    return dist[v][t] = INF;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    Graph g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add_edge(u, v);
    }
    for (int v = 1; v <= n; v++)
        sort(g.adj[v].begin(), g.adj[v].end());
    
    for (int v = 1; v <= n; v++)
        dfs(g, v, v);
    
    memset(dist, -1, sizeof(dist));
    for (int t = 1; t <= n; t++) {
        for (int v = 1; v <= n; v++) {
            if (dist[v][t] == -1)
                get_dist(g, v, t);
            // assert(dist[v][t] >= 0);
        }
    }

    for (int i = 0; i < q; i++) {
        int s, t, k;
        scanf("%d%d%d", &s, &t, &k);
        if (dist[s][t] < k - 1 || dist[s][t] == INF)
            printf("-1\n");
        else {
            // printf("dist[%d][%d] = %d\n", s, t, dist[s][t]);
            for (int v = 1; v <= n; v++) {
                // printf("dist[%d][%d] = %d, dist[%d][%d] = %d\n",
                //        s, v, dist[s][v], v, t, dist[v][t]);
                if (dist[s][v] == k - 1 && dist[v][t] == dist[s][t] - (k - 1)) {
                    printf("%d\n", v);
                    break;
                }
            }
        }
    }    
    return 0;
}
