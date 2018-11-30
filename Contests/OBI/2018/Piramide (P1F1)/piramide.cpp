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

int grid[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    int N;
    cin >> N;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            scanf("%d", &grid[r][c]);
    for (int c = 0; c < N; c++)
        dp[0][c] = grid[0][c];
    for (int r = 1; r < N; r++) {
        int acc = 0;
        for (int c = 0; c <= r; c++)
            acc += grid[r][c];
        for (int c = 0; c + r < N; c++) {
            dp[r][c] = acc + min(dp[r - 1][c], dp[r - 1][c + 1]);
            acc += grid[r][c + r + 1] - grid[r][c];
        }
    }
    printf("%d\n", dp[N - 1][0]);            
    return 0;
}
