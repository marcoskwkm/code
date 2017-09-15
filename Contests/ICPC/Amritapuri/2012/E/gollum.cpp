#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 410, MOD = (int)1e9 + 7;
const int MAXK = 12;

lint dp[MAXN][1 << MAXK];
int n, k;

lint go(int i, int mask) {
    mask &= (1 << k) - 1;
    if (k == 1) return 0;
    if (i == n) return 1;
    if (dp[i][mask] != -1) return dp[i][mask];
    bool safe[2] = {1, 1};
    if (i >= k - 1) {
        bool pal = 1;
        int l = 0, r = k - 3;
        while (l < r) {
            if (!!(mask & (1 << l)) != !!(mask & (1 << r))) {
                pal = 0;
                break;
            }
            l++, r--;
        }
        if (pal) safe[!!(mask & (1 << (k - 2)))] = 0;
    }
    if (i >= k) {
        bool pal = 1;
        int l = 0, r = k - 2;
        while (l < r) {
            if (!!(mask & (1 << l)) != !!(mask & (1 << r))) {
                pal = 0;
                break;
            }
            l++, r--;
        }
        if (pal) safe[!!(mask & (1 << (k - 1)))] = 0;
    }
    lint ret = 0;
    if (safe[0]) ret += go(i + 1, (mask << 1) + 0);
    if (safe[1]) ret += go(i + 1, (mask << 1) + 1);
    return dp[i][mask] = ret % MOD;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        memset(dp, -1, sizeof(dp));
        scanf("%d%d", &n, &k);
        printf("%lld\n", go(0, 0));
    }        
    return 0;
}
