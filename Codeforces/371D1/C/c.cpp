#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 3010;

lint dp[MAXN][MAXN];
int nxt[MAXN];
int n;
int v[MAXN];

lint go(int i, int j) {
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    memset(dp, -1, sizeof(dp));
    lint ans = LINF;
    for (int i = 1; i <= n; i++)
        ans = min(ans, go(0, i));
    printf("%lld\n", ans);
    return 0;
}
