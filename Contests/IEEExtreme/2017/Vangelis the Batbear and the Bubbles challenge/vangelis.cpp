#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

vector<int> adj[MAXN];
bool seen[MAXN];

bool dfs(int v, int prv) {
    seen[v] = 1;
    for (int nxt: adj[v]) {
        if (nxt == prv) continue;
        if (seen[nxt]) return 0;
        if (!dfs(nxt, v)) return 0;
    }
    return 1;
}

int main() {
    int t, n, m;
    for (cin >> t; t--;) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) adj[i].clear();
        memset(seen, 0, sizeof(seen));
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        bool ok = 1;
        for (int i = 0; i < n; i++)
            if (!seen[i] && !dfs(i, -1))
                ok = 0;
        printf("%d\n", ok ? 0 : 1);
    }
    return 0;
}
