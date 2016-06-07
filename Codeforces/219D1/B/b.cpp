#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 50;

int cnt[MAXN][MAXN][MAXN][MAXN];
int grid[MAXN][MAXN];
int acc[MAXN][MAXN];
int ans[MAXN][MAXN][MAXN][MAXN];

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            char sq;
            scanf(" %c", &sq);
            grid[r][c] = sq - '0';
            acc[r][c] = acc[r - 1][c] + acc[r][c - 1] - acc[r - 1][c - 1] + grid[r][c];
        }
    }
    for (int rlen = 1; rlen <= n; rlen++) {
        for (int clen = 1; clen <= m; clen++) {
            for (int r = 1; r + rlen - 1 <= n; r++) {
                for (int c = 1; c + clen - 1 <= m; c++) {
                    int rr = r + rlen - 1, cc = c + clen - 1;
                    int q1 = acc[rr][cc] - acc[r - 1][cc] - acc[rr][c - 1] + acc[r - 1][c - 1];
                    cnt[rlen][clen][r][c] = cnt[rlen][clen][r-1][c] + cnt[rlen][clen][r][c - 1] - cnt[rlen][clen][r - 1][c - 1] + (q1 == 0);
                }
            }
        }
    }

    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            for (int clen = 1; clen <= m; clen++) {
                for (int c1 = 1; c1 + clen - 1 <= m; c1++) {
                    int c2 = c1 + clen - 1;
                    ans[r1][r2][c1][c2] = ans[r1][r2][c1][c2 - 1] + ans[r1][r2][c1 + 1][c2]
                        - ans[r1][r2][c1 + 1][c2 - 1];
                    int add = 0;
                    int cnt = 0;
                    for (int i = r1; i <= r2; i++) {
                        int h = acc[i][c2] - acc[i][c1 - 1] - acc[i - 1][c2] + acc[i - 1][c1 - 1];
                        if (h == 0) cnt++;
                        else {
                            add += cnt * (cnt + 1) / 2;
                            cnt = 0;
                        }
                    }
                    add += cnt * (cnt + 1) / 2;
                    ans[r1][r2][c1][c2] += add;
//                    printf("ans[%d][%d][%d][%d] = %d\n", r1, r2, c1, c2, ans[r1][r2][c1][c2]);
                }
            }
        }
    }
                        
            

    while (q--) {
        int r1, r2, c1, c2;
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        // int ans = 0;
        // for (int rlen = 1; rlen <= r2 - r1 + 1; rlen++) {
        //     int add = 0;
        //     for (int clen = 1; clen <= c2 - c1 + 1; clen++) {
        //         int rr = r2 - rlen + 1, cc = c2 - clen + 1;
        //         int got = cnt[rlen][clen][rr][cc] - cnt[rlen][clen][r1 - 1][cc] - cnt[rlen][clen][rr][c1 - 1] + cnt[rlen][clen][r1 - 1][c1 - 1];
        //         if (got == 0) break;
        //         add += got;
        //     }
        //     ans += add;
        //     if (add == 0) break;
        // }
        // printf("%d\n", ans);
        printf("%d\n", ans[r1][r2][c1][c2]);
    }    
    return 0;
}
