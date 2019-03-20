#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int dp[MAXN][MAXN];
int v[MAXN];

int go(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int ret = INF;
    for (int i = l; i <= r; i++) {
        int sl = 0, sr = 0;
        for (int j = l; j < i; j++) sl += v[j];
        for (int j = i + 1; j <= r; j++) sr += v[j];
        ret = min(ret, sl + go(l, i - 1) + sr + go(i + 1, r));
    }
    return dp[l][r] = ret;
}

int main() {
    int n, t = 1;
    while (cin >> n && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);
        memset(dp, -1, sizeof(dp));
        printf("Teste %d\n%d\n\n", t++, go(0, n - 1));
    }        
    return 0;
}
