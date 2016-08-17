#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55, MAXC = 18;

char grid[MAXN][MAXN];
int dp[1 << MAXC][MAXN];

int get_dist(int r1, int c1, int r2, int c2) {
    int dr = abs(r2 - r1), dc = abs(c2 - c1);
    int lo = min(dr, dc);
    int ans = 3*lo;
    ans += 2*(dr + dc - 2*lo);
    return ans;
}

int cr[MAXN], cc[MAXN];

int main() {
    int n;
    while(scanf("%d", &n) && n) {
        int sr, sc;
        int n_coins = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                scanf(" %c", &grid[r][c]);
                if (grid[r][c] == 'D') {
                    sr = r, sc = c;
                }
                else if (grid[r][c] == 'M') {
                    cr[n_coins] = r;
                    cc[n_coins] = c;
                    n_coins++;
                }
            }
        }

        vector<int> masks;
        for (int mask = 0; mask < (1 << n_coins); mask++)
            masks.push_back(mask);
        sort(masks.begin(), masks.end(), [](int a, int b) {
            return __builtin_popcount(a) < __builtin_popcount(b);
        });

        memset(dp, INF, sizeof(dp));
        dp[0][0] = 0;
        for (int mask: masks) {
            if (mask == 0) {
                int r = sr, c = sc;
                for (int i = 0; i < n_coins; i++) {
                    int nxt_mask = mask | (1 << i);
                    dp[nxt_mask][i] = get_dist(r, c, cr[i], cc[i]);
                }
            }
            else {
                int mm = mask;
                while (mm) {
                    int bit = mm & -mm;
                    int i = __builtin_ctz(bit);
                    mm -= bit;

                    for (int j = 0; j < n_coins; j++) {
                        if (mask & (1 << j)) continue;
                        int nxt_mask = mask | (1 << j);
                        dp[nxt_mask][j] = min(dp[nxt_mask][j], dp[mask][i] + get_dist(cr[i], cc[i], cr[j], cc[j]));
                    }
                }
            }
        }

        int ans = INF;
        for (int i = 0; i < n_coins; i++)
            ans = min(ans, dp[(1 << n_coins) - 1][i] + get_dist(cr[i], cc[i], sr, sc));

        printf("%d\n", ans);
    }            
    return 0;
}
