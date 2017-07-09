#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 4000;
const int MOD = (int)1e9 + 7;

lint dp[MAXN][MAXN];
lint acc[MAXN][MAXN], accd[MAXN][MAXN];
int n, d, t, k;

int main() {
    cin >> n >> d >> t >> k;
    dp[0][0] = 1;
    acc[0][0] = accd[0][0] = k;
    for (int q = 0; q <= t; q++) {
        for (int i = 1; i <= n; i++) {
            dp[q][i] += acc[q][i - 1];
            if (i - d >= 0) dp[q][i] -= acc[q][i - d];
            if (q >= 1 && i >= d) dp[q][i] += accd[q - 1][i - d];
            dp[q][i] %= MOD;
            acc[q][i] = (acc[q][i - 1] + (k - 1) * dp[q][i]) % MOD;
            if (q == 0) accd[q][i] = (k - 1) * dp[q][i] % MOD;
            else accd[q][i] = (accd[q - 1][i - 1] + (k - 1) * dp[q][i]) % MOD;            
        }
    }
    printf("%lld\n", (dp[t][n] % MOD + MOD) % MOD);    
    return 0;
}
