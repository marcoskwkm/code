#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 20;

int dp[MAXD][MAXD][MAXD];
int q[MAXD][MAXD][MAXD];

int go(int f, int y, int x) {
    if (f < 1 || x > 10 || y > 10) return 0;
    if (dp[f][y][x] != -1) return dp[f][y][x];
    return dp[f][y][x] = q[f][y][x] + max(max(go(f, y, x + 1), go(f, y + 1, x)), go(f - 1, y, x));
}

int main() {
    #ifndef HOME
    freopen("commandos.in", "r", stdin);
    #endif

    int t;
    for (scanf("%d", &t); t--;) {
        memset(q, 0, sizeof(q));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n ; i++) {
            int f, y, x, h;
            scanf("%d%d%d%d", &f, &y, &x, &h);
            q[f][y][x] += h;
        }
        memset(dp, -1, sizeof(dp));
        printf("%d\n", go(10, 1, 1));
    }                
    return 0;
}
