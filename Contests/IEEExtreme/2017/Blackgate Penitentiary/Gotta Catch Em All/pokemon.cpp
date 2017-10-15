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

int grid[MAXN][MAXN];
int dp[MAXN][MAXN];
int n, m;

int check(int h) {
    grid[1][1] = h;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            dp[r][c] = (r == 1 && c == 1 ? 0 : max(dp[r][c - 1], dp[r - 1][c])) + grid[r][c];
            if (dp[r][c] <= 0) dp[r][c] = -INF;
        }
    }
    return dp[n][m] > 0;
}

int main() {
    for (int i = 0; i < MAXN; i++)
        dp[0][i] = dp[i][0] = -INF;
    cin >> n >> m;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            scanf("%d", &grid[r][c]);
            assert(-1000 <= grid[r][c] && grid[r][c] <= 1000);
        }
    }
    
    int l = 1, r = INF;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
