#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MAXK = 510;

int dp[2][MAXN];
int hi[2][MAXN];
int p[MAXN], c[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &p[i]);
    for (int i = 1; i < n; i++) scanf("%d", &c[i]);
    int cur = 0, prv = 1;
    for (int i = n - 1; i >= 0; i--) {
        hi[prv][i] = max(hi[prv][i + 1], p[i] + c[i]);
    }    
    for (int kk = 1; kk <= k; kk++) {
        for (int i = n - 1; i >= 0; i--) {
            dp[cur][i] = max(dp[cur][i + 1], hi[prv][i + 1] - p[i]);
            hi[cur][i] = max(dp[cur][i] + p[i] + c[i], hi[cur][i + 1]);
        }
        cur ^= 1, prv ^= 1;
    }
    printf("%d\n", dp[prv][0]);    
    return 0;
}
