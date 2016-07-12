#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXH = (int)1e6 + 10;

lint dp[MAXH];

int main() {
    lint H, B, b, c[3];
    while(scanf("%lld%lld%lld%lld%lld%lld", &H, &B, &b, &c[0], &c[1], &c[2]) > 0) {
        memset(dp, 0, sizeof(dp));
        lint ans = 0;
        for (int h = 0; h <= H; h++) {
            ans = max(ans, dp[h]);
            for (int i = 0; i < 3; i++) {
                if (h + c[i] <= H) {
                    lint L = (H - h - c[i])*(B - b)/H + b;
                    lint q = L / c[i];
                    dp[h + c[i]] = max(dp[h + c[i]], dp[h] + q*q*c[i]*c[i]*c[i]);
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
