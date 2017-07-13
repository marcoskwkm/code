#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

lint dp[MAXN][MAXN][MAXN];
vector<pii> adj[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u].push_back(pii(v, c));
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                dp[i][j][k] = -LINF;
    for (int i = 1; i <= n; i++)
        dp[0][i][i] = 0;
    for (int k = 1; k <= n; k++) { // O(N)
        for (int s = 1; s <= n; s++) { // O(N)
            for (int v = 1; v <= n; v++) { // O(E)
                for (pii edge: adj[v]) {
                    int nxt, cst;
                    tie(nxt, cst) = edge;
                    dp[k][s][nxt] = max(dp[k][s][nxt], dp[k - 1][s][v] + cst);
                }
            }
        }
    }
    long double ans = 0;
    for (int s = 1; s <= n; s++)
        for (int len = 2; len <= n; len++)
            ans = max(ans, (long double)(dp[len][s][s]) / len);
    printf("%.12Lf\n", ans);    
    return 0;
}
