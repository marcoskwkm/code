#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXP = 62;

lint dp[MAXP][3];

int main() {
    lint n;
    dp[0][0] = 1;
    for (int i = 1; i < MAXP; i++) {
        dp[i][0] += dp[i - 1][2] + dp[i - 1][0];
        dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
        dp[i][2] += dp[i - 1][1] + dp[i - 1][2];
    }    
    while (scanf("%lld", &n) > 0) {
        lint ans = 0;
        int mod = 0;
        for (int i = MAXP - 1; i >= 0; i--) {
            if (n & (1ll << i)) {
                ans += dp[i][mod];
                // printf("ans += %lld\n", dp[i][mod]);
                mod = (mod + 2)%3;
            }
        }
        ans += dp[0][mod];
        printf("Day %lld: Level = %lld\n", n, ans - 1);
    }        
    return 0;
}
