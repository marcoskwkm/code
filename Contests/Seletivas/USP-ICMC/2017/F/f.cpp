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
const int LOG = 30;

vector<int> adj[MAXN];
int sum[LOG][MAXN];
int total_sum[LOG];
int w[MAXN];

void dfs(int v, int depth) {
    total_sum[depth] += w[v];
    sum[depth][v] += w[v];
    for (int nxt: adj[v]) {
        dfs(nxt, depth + 1);
        for (int d = 0; d < LOG; d++)
            sum[d][v] += sum[d][nxt];
    }
}

int main() {
    int n, m;
    cin >> n >> m >> w[1];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        cin >> w[u];
        adj[v].push_back(u);
    }

    dfs(1, 0);
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        int ans = 0;
        for (int d = 0; d < LOG; d++)
            ans = max(ans, total_sum[d] - sum[d][x]);
        printf("%d\n", ans);
    }    
    return 0;
}
