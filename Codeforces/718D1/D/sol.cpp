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
const int NEIGHBORHOOD_SIZE = 850;
const int MAXK = 21;

lint dp[MAXN][MAXN][MAXK];
int cst_r[MAXN][MAXN], cst_c[MAXN][MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    if (k % 2) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                printf("-1 ");
            }
            printf("\n");
        }
        return 0;
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c + 1 < m; c++) {
            scanf("%d", &cst_c[r][c]);
        }
    }
    for (int r = 0; r + 1 < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf("%d", &cst_r[r][c]);
        }
    }

    memset(dp, INF, sizeof(dp));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            dp[r][c][0] = 0;
        }
    }

    for (int d = 1; 2 * d <= k; d++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (r > 0) {
                    dp[r][c][d] = min(dp[r][c][d], dp[r - 1][c][d - 1] + cst_r[r - 1][c]);
                }
                if (r + 1 < n) {
                    dp[r][c][d] = min(dp[r][c][d], dp[r + 1][c][d - 1] + cst_r[r][c]);
                }
                if (c > 0) {
                    dp[r][c][d] = min(dp[r][c][d], dp[r][c - 1][d - 1] + cst_c[r][c - 1]);
                }
                if (c + 1 < m) {
                    dp[r][c][d] = min(dp[r][c][d], dp[r][c + 1][d - 1] + cst_c[r][c]);
                }
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            printf("%lld ", 2 * dp[r][c][k / 2]);
        }
        printf("\n");
    }
    return 0;
}
