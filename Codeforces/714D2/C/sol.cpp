#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = (int)2e5 + 10;
const int MOD = (int)1e9 + 7;

lint dp[MAXM][10];

int main() {
    for (int i = 0; i < 10; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < MAXM; i++) {
        for (int d = 0; d < 10; d++) {
            dp[i][d] = (d == 9 ? dp[i - 1][1] + dp[i - 1][0] : dp[i - 1][d + 1]) % MOD;
        }
    }

    int t;
    for (cin >> t; t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        lint ans = 0;
        while (n) {
            ans += dp[m][n % 10];
            n /= 10;
        }
        printf("%lld\n", ans % MOD);
    }

    return 0;
}
