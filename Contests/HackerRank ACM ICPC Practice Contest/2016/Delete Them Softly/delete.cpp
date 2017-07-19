#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210;

// dp[l][r][k] means: What is the best contribution of the elements in [l, r],
// knowing that there are k elements to the right of r that can be taken at any
// time?
lint dp[MAXN][MAXN][MAXN];
lint v[MAXN], acc[MAXN];
int max_l[MAXN], min_r[MAXN];

lint go(int l, int r, int k) {
    if (l > r) return 0;
    if (dp[l][r][k] != -1) return dp[l][r][k];
    if (l == r) return dp[l][r][k] = max(0LL, v[l]) * k;
    lint ret = -LINF;

    // We choose the first element to take in this interval
    for (int i = l; i <= r; i++) {
        // Is there an active dependency blocking i?
        if (max_l[i] >= l || min_r[i] <= r) continue;

        // Here we decide to take all k elements to the right before taking
        // the first element in [l, r].
        ret = max(ret,
                  (acc[r] - acc[l - 1]) * k // what we gain from taking all k
                                            // elements to the right
                  + acc[i - 1] - acc[l - 1] // what we gain from taking i first
                  + go(l, i - 1, r - i)     // what we gain from [l, i - 1]
                  + go(i + 1, r, 0));       // what we gain from [i + 1, r]

        // Here we do not take any of the k elements before taking i. Note that
        // it is always optimal to take all k elements at once (when the current
        // sum of elements in [l, r] is maximal).
        ret = max(ret,
                  acc[i - 1] - acc[l - 1]   // what we gain from taking i first
                  + go(l, i - 1, k + r - i) // what we gain from [l, i - 1]
                  + go(i + 1, r, k));       // what we gain from [i + 1, r]
    }
    return dp[l][r][k] = ret;
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        acc[i] = acc[i - 1] + v[i];
        max_l[i] = -INF, min_r[i] = INF;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x < y) max_l[y] = max(max_l[y], x);
        else min_r[y] = min(min_r[y], x);
    }

    memset(dp, -1, sizeof(dp));
    if (go(1, n, 0) == -LINF) printf("Impossible\n");
    else printf("%lld\n", go(1, n, 0));        
    return 0;
}
