#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 5010;

lint dp[2][MAXN];
int v[MAXN];
int ord[MAXN];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        ord[i] = i;
        scanf("%d", &v[i]);
    }

    sort(ord, ord + n, [](int a, int b) { return v[a] < v[b]; });
    memset(dp, INF, sizeof(dp));
    dp[0][0] = 0;
    int cur = 0, nxt = 1;
    lint ans = LINF;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            dp[nxt][i] = min(dp[nxt][i], dp[cur][i]);
            dp[cur][i + 1] = min(dp[cur][i + 1], abs(v[i] - v[ord[j]]) + dp[cur][i]);
        }
        ans = min(ans, dp[cur][n]);
        cur ^= 1, nxt ^= 1;
        memset(dp[nxt], INF, sizeof(dp[nxt]));
    }
    
    cout << ans << endl;    
    return 0;
}
