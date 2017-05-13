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

int dp[MAXN][MAXN][MAXN][5];
int q[5];

int go(int q1, int q2, int q3, int r, int p) {
    if (dp[q1][q2][q3][r] != -1) return dp[q1][q2][q3][r];
    int ret = 0;
    if (q1 > 0) ret = max(ret, (r == 0) + go(q1 - 1, q2, q3, (p - 1 + r) % p, p));
    if (q2 > 0) ret = max(ret, (r == 0) + go(q1, q2 - 1, q3, (p - 2 + r) % p, p));
    if (q3 > 0) ret = max(ret, (r == 0) + go(q1, q2, q3 - 1, (p - 3 + r) % p, p));
    return dp[q1][q2][q3][r] = ret;
}    

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        memset(dp, -1, sizeof(dp));
        memset(q, 0, sizeof(q));
        printf("Case #%d: ", t);
        int n, p;
        scanf("%d%d", &n, &p);
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            q[x % p]++;
        }
        printf("%d\n", q[0] + go(q[1], q[2], q[3], 0, p));
    }        
    return 0;
}
