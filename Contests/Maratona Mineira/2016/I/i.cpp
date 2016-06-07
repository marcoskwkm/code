#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

lint dp[MAXN][MAXN];
lint cost[MAXN][MAXN];
int v[MAXN];
lint acc[MAXN];

lint getcost(int l, int r) {
    if (cost[l][r] != LINF) return cost[l][r];
    lint cst = 0;
    for (int i = l; i <= r; i++)
        cst += v[i] * (i - l);
    lint ret = cst;
    for (int i = l + 1; i <= r; i++) {
        cst += acc[i - 1] - acc[l - 1];
        cst -= acc[r] - acc[i - 1];
        ret = min(ret, cst);
    }
    return cost[l][r] = ret;
}

lint go(int n, int k) {
    if (n == 0) return 0;
    if (k == 0) return LINF;
    if (dp[n][k] != LINF) return dp[n][k];
    for (int i = n; i > 0; i--)
        dp[n][k] = min(dp[n][k], getcost(i, n) + go(i - 1, k - 1));
    return dp[n][k];
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        acc[i] = acc[i - 1] + v[i];
    }
    memset(dp, INF, sizeof(dp));
    memset(cost, INF, sizeof(cost));
    printf("%lld\n", go(n, k));
    return 0;
}
