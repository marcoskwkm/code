#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10, MAXK = 310;

vector<int> adj[MAXN];
int dp[MAXN][MAXK];
int l[MAXN], r[MAXN];
int wealth[MAXN];
bool done[MAXN];
int n, k;

void dfs(int v) {
    if (adj[v].empty()) {
        l[v] = r[v];
        return;
    }
    l[v] = adj[v][0];
    for (int i = 0; i < (int)adj[v].size(); i++) {
        int nxt = adj[v][i];
        if (i + 1 < (int)adj[v].size()) r[nxt] = adj[v][i + 1];
        else r[nxt] = r[v];
        dfs(nxt);
    }
}

void go(int v) {
    if (done[v]) return;
    done[v] = 1;
    dp[v][0] = 0;
    dp[v][1] = wealth[v];
    if (l[v] != -1) {
        go(l[v]);
        for (int kk = 1; kk <= k; kk++)
            dp[v][kk] = max(dp[v][kk], dp[l[v]][kk]);
    }
    if (r[v] != -1) {
        go(r[v]);
        for (int kk = 1; kk <= k; kk++)
            dp[v][kk] = max(dp[v][kk], dp[r[v]][kk - 1] + wealth[v]);
    }
}

int main() {
    while (scanf("%d%d", &n, &k) > 0) {
        for (int v = 1; v <= n; v++) {
            adj[v].clear();
            fill(dp[v], dp[v] + k + 10, -INF);
            l[v] = r[v] = -1;
            done[v] = 0;
        }
        int root = -1;
        for (int v = 1; v <= n; v++) {
            int p;
            scanf("%d%d", &p, &wealth[v]);
            if (p == 0) root = v;
            else adj[p].push_back(v);
        }
        dfs(root);
        go(root);
        if (dp[root][k] < 0) printf("impossible\n");
        else printf("%d\n", dp[root][k]);
    }    
    return 0;
}
