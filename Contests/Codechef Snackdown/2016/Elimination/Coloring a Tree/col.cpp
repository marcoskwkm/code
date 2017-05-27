#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 60;
const int MOD = (int)1e9 + 7;

lint C[MAXN][MAXN];

lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    if (C[n][k] != -1) return C[n][k];
    if (k == 0) return C[n][k] = 1;
    return C[n][k] = (choose(n - 1, k - 1) + choose(n - 1, k)) % MOD;
}

int main() {
    int t;
    memset(C, -1, sizeof(C));
    for (scanf("%d", &t); t--;) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i < n; i++) scanf("%*d%*d");
        lint A = k;
        lint ans = 0;
        for (int i = 1; i <= k; i++) {
            ans += choose(n - 1, i - 1) * A % MOD;
            A = A * (k - i) % MOD;
        }
        printf("%lld\n", ans % MOD);
    }
    return 0;
}
