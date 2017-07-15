#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 20;

vector<int> adj[MAXN];
lint dp[1 << MAXN][MAXN];
bool seen[1 << MAXN][MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<pii> q;
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 1;
        seen[1 << i][i] = 1;
        q.push(pii(1 << i, i));
    }
    while (!q.empty()) {
        int mask, i;
        tie(mask, i) = q.front();
        q.pop();
        for (int nxt: adj[i]) {
            if (mask & (1 << nxt)) continue;
            int nxtm = mask | (1 << nxt);
            dp[nxtm][nxt] += dp[mask][i];
            if (!seen[nxtm][nxt]) {
                q.push(pii(nxtm, nxt));
                seen[nxtm][nxt] = 1;
            }
        }
    }
    lint ans = 0;
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++)
            ans += dp[mask][i];
        
    cout << ans - n << endl;    
    return 0;
}
