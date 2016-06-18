#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e7 + 10;
const int LOG = 30;
const int MOD = (int)1e9 + 7;
const int MAXQ = (int)2.5e7 + 10;

vector<int> adj[MAXN];
int up[LOG][MAXN];
int depth[MAXN];
vector<pii> plows[MAXN];

void dfs(int v, int prv, int d) {
    depth[v] = d;
    printf("depth[%d] = %d\n", v, depth[v]);
    up[0][v] = (prv == -1 ? v : prv);
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        dfs(nxt, v, d + 1);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[v] - (1 << i) >= depth[u])
            v = up[i][v];
    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int snow[MAXQ];
set< pii, greater<pii> > s[MAXN];
int is[MAXN];

lint go(int v, int prv) {
    int maxlen = 0, at = -1;
    lint ret = 0;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        ret += go(nxt, v);        
        if ((int)s[is[nxt]].size() > maxlen) {
            maxlen = s[is[nxt]].size();
            at = nxt;
        }
    }
    for (int nxt: adj[v]) {
        if (nxt == at) continue;
        for (const pii &p: s[is[nxt]])
            s[is[at]].insert(p);
    }
    if (at == -1) is[v] = v;
    else is[v] = is[at];
    for (const pii &p: plows[v])
        s[is[v]].insert(p);

    while (!s[is[v]].empty() && s[is[v]].begin()->second >= depth[v])
        s[is[v]].erase(s[is[v]].begin());

    if (!s[is[v]].empty()) {
        printf("%d: using plow with time = %d (removed %d)\n", v, s[is[v]].begin()->first,
               snow[s[is[v]].begin()->first]);
        ret += snow[s[is[v]].begin()->first];
    }
    else printf("%d: no plows available\n", v);
    return ret % MOD;
}

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int n, q;
        scanf("%d%d", &n, &q);
        for (int v = 1; v <= n; v++) {
            plows[v].clear();
            adj[v].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, -1, 0);
        int cur_snow = 0;
        for (int i = 0; i < q; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            int v = lca(a, b);
            plows[a].push_back(pii(i + depth, depth[v]));
            plows[b].push_back(pii(i, depth[v]));
            snow[i] = cur_snow;
            if (c) cur_snow++;
        }
        printf("%lld\n", go(1, -1));
    }

    return 0;
}
