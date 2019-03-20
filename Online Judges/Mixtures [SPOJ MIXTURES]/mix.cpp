#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int dp[MAXN][MAXN];
int v[MAXN];

int go(int l, int r) {
    if (l == r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int ret = INF;
    for (int i = l; i < r; i++) {
        int cl = 0, cr = 0;
        for (int j = l; j <= i; j++) cl += v[j];
        for (int j = i + 1; j <= r; j++) cr += v[j];
        cl %= 100, cr %= 100;
        ret = min(ret, cl * cr + go(l, i) + go(i + 1, r));
    }
    return dp[l][r] = ret;
}    

int main() {
    int n;
    while (scanf("%d", &n) > 0) {
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);
        memset(dp, -1, sizeof(dp));
        printf("%d\n", go(0, n - 1));
    }        
    return 0;
}
