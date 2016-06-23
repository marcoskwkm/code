#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<pii> adj[MAXN];
int a[MAXN];

int dfs(int v, int prv, lint d) {
    if (d > a[v]) return 0;
    int ret = 1;
    for (pii edge: adj[v]) {
        int nxt = edge.first, cst = edge.second;
        if (nxt != prv)
            ret += dfs(nxt, v, max(d + cst, 0ll));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int v = 2; v <= n; v++) {
        int u, c;
        scanf("%d%d", &u, &c);
        adj[u].push_back(pii(v, c));
        adj[v].push_back(pii(u, c));
    }
    printf("%d\n", n - dfs(1, -1, 0));
    return 0;
}
