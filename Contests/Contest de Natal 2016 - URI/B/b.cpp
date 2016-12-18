#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10, MAXK = 510;

lint dp[MAXK][MAXN];
int v[MAXN];
lint s[MAXN];

void solve(int k, int l, int r, int opt_l, int opt_r) {
    if (l > r) return;
    int mid = (l + r) / 2;
    lint best = LINF;
    int opt = -1;
    for (int i = opt_l; i <= min(mid - 1, opt_r); i++) {
        lint got = dp[k - 1][i] + (s[mid] - s[i]) * (mid - i);
        if (got < best) {
            best = got;
            opt = i;
        }
    }
    dp[k][mid] = best;
    if (l < r) {
        solve(k, l, mid - 1, opt_l, opt);
        solve(k, mid + 1, r, opt, opt_r);
    }
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        s[i] = s[i - 1] + v[i];
        dp[0][i] = LINF;
    }
    for (int kk = 1; kk <= k; kk++)
        solve(kk, 1, n, 0, n - 1);
    printf("%lld\n", dp[k][n]);        
    return 0;
}
