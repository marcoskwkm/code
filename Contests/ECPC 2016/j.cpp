#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10, LOG = 20;

vector<pii> adj[MAXN];
int up[LOG][MAXN];
lint cost[LOG][MAXN];
int delta[MAXN];
int x[MAXN];
int ans[MAXN];

void dfs(int v, int prv, int cst) {
    up[0][v] = prv;
    cost[0][v] = cst;
    for (int i = 1; i < LOG; i++) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        cost[i][v] = cost[i - 1][v] + cost[i - 1][up[i - 1][v]];
    }
    int cur = v;
    lint acc = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        if (acc + cost[i][cur] <= x[v]) {
            acc += cost[i][cur];
            cur = up[i][cur];
        }
    }
    if (v != 1) {
        if (cur != 1) delta[up[0][cur]]--;
        delta[up[0][v]]++;
    }
    for (pii edge: adj[v]) {
        int nxt, c;
        tie(nxt, c) = edge;
        if (nxt == prv) continue;
        dfs(nxt, v, c);
    }
}

int propagate(int v, int prv) {
    ans[v] = 0;
    for (pii edge: adj[v]) {
        if (edge.first == prv) continue;
        ans[v] += propagate(edge.first, v);
    }
    ans[v] += delta[v];
    return ans[v];
}    

int main() {
    #ifndef HOME
    freopen("car.in", "r", stdin);
    #endif
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x[i]);
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            adj[u].push_back(pii(v, c));
            adj[v].push_back(pii(u, c));
        }
        memset(delta, 0, sizeof(delta));
        dfs(1, 1, 0);
        propagate(1, 1);
        for (int v = 1; v <= n; v++)
            printf("%d ", ans[v]);
        printf("\n");
    }
}
