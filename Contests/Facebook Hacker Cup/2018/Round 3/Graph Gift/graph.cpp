#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 30010;

lint v[MAXN];
lint dp[3][MAXN];

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        debug("Case %d...\n", t);
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            scanf("%lld", &v[i]);
        sort(v, v + n);
        memset(dp[0], 0, sizeof(dp[0]));
        memset(dp[1], INF, sizeof(dp[1]));
        debug("%lld\n", dp[1][0]);
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                dp[len % 3][i] = min(dp[(len - 2) % 3][i + 1], dp[(len - 1) % 3][i]) + v[i] * v[i + len - 1];
                if (v[i + len - 1] < 0) dp[len % 3][i] = min(dp[len % 3][i], dp[(len - 1) % 3][i + 1] + v[i] * v[i + len - 1]);
            }
        }
        printf("Case #%d: %lld\n", t, dp[n % 3][0]);
    }            
    return 0;
}
