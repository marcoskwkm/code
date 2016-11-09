#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;
const int MOD = (int)1e9 + 7;

lint dp[MAXN][MAXN];

lint go(int n, int k) {
    if (k > n) return 0;
    if (k == 1) return 1;
    if (dp[n][k] != -1) return dp[n][k];
    return dp[n][k] = (k * go(n - 1, k) + k * go(n - 1, k - 1)) % MOD;
}

int main() {
    #ifndef HOME
    freopen("galactic.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        int n, k;
        scanf("%d%d", &n, &k);
        memset(dp, -1, sizeof(dp));
        cout << go(n, k) << endl;
    }
    return 0;
}
