#include "asteroids.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 1010;

int grid[MAXD][MAXD];
int dp[MAXD][MAXD];
int N, M;

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    if (thisId > 0) return 0;
    N = GetHeight(), M = GetWidth();
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            char got = GetPosition(r, c);            
            grid[r][c] = (got == '#' ? -1 : got - '0');
        }
    }
    int ans = -1;
    for (int r = N - 1; r >= 0; r--) {
        for (int c = 0; c < M; c++) {
            dp[r][c] = -1;
            if (grid[r][c] == -1) continue;
            if (grid[r + 1][c] != -1 && dp[r + 1][c] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c] + grid[r][c]);
            if (c > 0 && grid[r + 1][c - 1] != -1 && grid[r][c - 1] != -1 && dp[r + 1][c - 1] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c - 1] + grid[r][c - 1] + grid[r][c]);
            if (c + 1 < M && grid[r + 1][c + 1] != -1 && grid[r][c + 1] != -1 && dp[r + 1][c + 1] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c + 1] + grid[r][c + 1] + grid[r][c]);
            if (r == 0) ans = max(ans, dp[r][c]);
        }
    }
    printf("%d\n", ans);    
    return 0;
}
