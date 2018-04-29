// small 1 and 2

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 300;

int dp[MAXN][MAXN];
int v[MAXN];
int n, l;

int go(int q, int i) {
    if (dp[q][i] != -1) return dp[q][i];
    int x = v[i];
    if (i == l) x = 0;
    int ret = 0;
    for (int take = (x == 0); take <= q; take++)
        ret = max(ret, (200 * (x + take) + n) / (2 * n) + go(q - take, i + (x != 0)));
    return dp[q][i] = ret;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);
        cin >> n >> l;
        int sumv = 0;
        for (int i = 0; i < l; i++) {
            scanf("%d", &v[i]);
            sumv += v[i];
        }
        memset(dp, -1, sizeof(dp));
        printf("%d\n", go(n - sumv, 0));
    }        
    return 0;
}
