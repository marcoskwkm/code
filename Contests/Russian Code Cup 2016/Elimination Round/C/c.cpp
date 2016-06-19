#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int MOD = (int)1e9 + 7;

vector<int> adj[MAXN];
int dist[2][MAXN];

void dfs(int v, int d, int k, int prv) {
    dist[k][v] = d;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, d + 1, k, v);
    }
}

lint modexp(int b, int e) {
    if (e == 0) return 1;
    lint aux = modexp(b, e / 2);
    if (e & 1) return aux * aux % MOD * b % MOD;
    return aux * aux % MOD;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int v = 1; v <= n; v++) {
            adj[v].clear();
            dist[0][v] = dist[1][v] = -1;
        }
        bool ok = 1;
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
            if (adj[u].size() > 3 || adj[v].size() > 3) ok = 0;
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
                   
        dfs(1, 0, 0, -1);
        int maxd = -1, nv = 1;
        for (int v = 1; v <= n; v++) {
            if (dist[0][v] > maxd) {
                maxd = dist[0][v];
                nv = v;
            }
        }
        dfs(nv, 0, 1, -1);
        maxd = -1, nv = 1;
        for (int v = 1; v <= n; v++) {
            if (dist[1][v] > maxd) {
                maxd = dist[1][v];
                nv = v;
            }
        }
        dfs(nv, 0, 0, -1);

        int mind = INF, ansv = 1;
        for (int v = 1; v <= n; v++) {
            if (adj[v].size() > 2) continue;
            int d = max(dist[0][v], dist[1][v]);
            if (d < mind) {
                mind = d;
                ansv = v;
            }
        }

        if (mind == INF) {
            printf("-1\n");
            continue;
        }
        lint ans = modexp(2, mind + 1) - 1 - n;
        ans = (ans % MOD + MOD) % MOD;
        printf("%d %lld\n", ansv, ans);
    }        
    return 0;
}
