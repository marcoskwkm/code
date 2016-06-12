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
    N = GetHeight(), M = GetWidth();
    int mm = (M + m - 1) / m;
    int L = thisId * mm, R = min(M, (thisId + 1) * mm);
    int LL = max(0, (thisId - 1) * mm), RR = min(M, (thisId + 2) * mm);
    for (int r = 0; r < N; r++) {
        for (int c = LL; c < RR; c++) {
            char got = GetPosition(r, c);            
            grid[r][c] = (got == '#' ? -1 : got - '0');
        }
    }
    
    int top = N - 1;
    int split = min(8, mm);
    for (int r = N - 1; r >= 0; r--) {
        for (int c = LL; c < RR; c++) {
            dp[r][c] = -1;
            if (grid[r][c] == -1) continue;
            if (grid[r + 1][c] != -1 && dp[r + 1][c] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c] + grid[r][c]);
            if (c > LL && grid[r + 1][c - 1] != -1 && grid[r][c - 1] != -1 && dp[r + 1][c - 1] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c - 1] + grid[r][c - 1] + grid[r][c]);
            if (c + 1 < RR && grid[r + 1][c + 1] != -1 && grid[r][c + 1] != -1 && dp[r + 1][c + 1] != -1)
                dp[r][c] = max(dp[r][c], dp[r + 1][c + 1] + grid[r][c + 1] + grid[r][c]);
        }
        if (r % split == 0) {
            if (thisId > 0) {
                for (int rr = top; rr >= r; rr--)
                    for (int c = LL; c < R; c++)
                        PutInt(thisId - 1, dp[rr][c]);
                Send(thisId - 1);
            }
            if (thisId + 1 < m) {
                for (int rr = top; rr >= r; rr--)
                    for (int c = L; c < RR; c++)
                        PutInt(thisId + 1, dp[rr][c]);
                Send(thisId + 1);
            }

            if (thisId > 0) {
                Receive(thisId - 1);
                for (int rr = top; rr >= r; rr--)
                    for (int c = LL; c < R; c++)
                        dp[rr][c] = max(dp[rr][c], GetInt(thisId - 1));
            }
            if (thisId + 1 < m) {
                Receive(thisId + 1);
                for (int rr = top; rr >= r; rr--)
                    for (int c = L; c < RR; c++)
                        dp[rr][c] = max(dp[rr][c], GetInt(thisId + 1));
            }
            top = r - 1;
        }
    }

    int best = -1;
    for (int c = LL; c < RR; c++) {
        best = max(best, dp[0][c]);
    }
    PutInt(0, best);
    Send(0);

    if (thisId == 0) {
        int ans = -1;
        for (int i = 0; i < m; i++) {
            Receive(i);
            ans = max(ans, GetInt(i));
        }
        printf("%d\n", ans);
    }
    return 0;
}
