#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

vector<int> adj[MAXN];
int val[MAXN], depth[MAXN];
int acc[2][MAXN];
int up[LOG][MAXN];
int low[2][LOG][MAXN];

void dfs(int v, int prv, int v0, int v1, int d) {
    depth[v] = d;
    up[0][v] = prv;
    acc[0][v] = v0;
    acc[1][v] = v1;
    low[0][0][v] = v0;
    low[1][0][v] = v1;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v, v0 + val[nxt], v1 - val[v], d + 1);
    }
}

bool check(int u, int v) {
    int uu = u, vv = v;
    int l0 = INF, l1 = INF;
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[up[i][u]] >= depth[v]) {
            l1 = min(l1, low[1][i][u]);
            u = up[i][u];
        }
        if (depth[up[i][v]] >= depth[u]) {
            l0 = min(l0, low[0][i][v]);
            v = up[i][v];
        }
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            l1 = min(l1, low[1][i][u]);
            l0 = min(l0, low[0][i][v]);
            u = up[i][u], v = up[i][v];
        }
    }
    if (u != v) {
        l1 = min(l1, low[1][0][u]);
        l0 = min(l0, low[0][0][v]);
        u = v = up[0][u];
    }
    l1 = min(l1, acc[1][u]);
    l0 = min(l0, acc[0][u]);
    int delta = acc[1][u] - acc[0][u];
    int diff = acc[1][uu] - val[uu];
    if (l1 - diff < 0 || l0 + delta - diff < 0) return 0;
    if (acc[0][vv] + delta - diff != 0) return 0;
    return 1;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, q;
        scanf("%d%d", &n, &q);
        for (int v = 1; v <= n; v++)
            adj[v].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int v = 1; v <= n; v++) {
            char c;
            scanf(" %c", &c);
            val[v] = (c == '(' ? 1 : -1);
        }
        dfs(1, 1, 0, 0, 0);
        for (int i = 1; i < LOG; i++) {
            for (int v = 1; v <= n; v++) {
                up[i][v] = up[i - 1][up[i - 1][v]];
                low[0][i][v] = min(low[0][i - 1][v], low[0][i - 1][up[i - 1][v]]);
                low[1][i][v] = min(low[1][i - 1][v], low[1][i - 1][up[i - 1][v]]);
            }
        }

        while (q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%s\n", check(u, v) ? "Yes" : "No");
        }
    }        
    return 0;
}
