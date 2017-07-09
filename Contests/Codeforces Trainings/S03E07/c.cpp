#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;
const int MOD = (int)1e9 + 7;

set<int> adj[MAXN];
lint ch[MAXN][MAXN];

lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    if (k == 0) return 1;
    if (ch[n][k] != -1) return ch[n][k];
    return ch[n][k] = (choose(n - 1, k) + choose(n - 1, k - 1)) % MOD;
}

int main() {
    memset(ch, -1, sizeof(ch));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    lint ans = 0;
    for (int v = 1; v <= n; v++) {
        if (adj[v].size() < 4) continue;
        for (int w: adj[v]) {
            if (adj[w].size() < 3) continue;
            int common = 0;
            for (int u: adj[w])
                if (adj[v].find(u) != adj[v].end())
                    common++;
            for (int i = 0; i <= 3; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j > common) break;
                    ans += choose(adj[v].size() - common - 1, 3 - i) *
                        choose(adj[w].size() - common - 1, 2 - j) % MOD *
                        choose(common, i) % MOD * choose(common - i, j);
                    ans %= MOD;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
