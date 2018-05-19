#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;
const int MAGIC = 35;

int dp[MAXN][MAXN];

int main() {
    for (int r = 0; r <= MAGIC; r++) {
        for (int b = 0; b <= MAGIC; b++) {
            if (r == 0 && b == 0) continue;
            for (int i = MAXN - 1; i >= r; i--)
                for (int j = MAXN - 1; j >= b; j--)
                    dp[i][j] = max(dp[i][j], 1 + dp[i - r][j - b]);
        }
    }
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int R, B;
        scanf("%d%d", &R, &B);
        printf("Case #%d: %d\n", t, dp[R][B]);
    }        
    return 0;
}
