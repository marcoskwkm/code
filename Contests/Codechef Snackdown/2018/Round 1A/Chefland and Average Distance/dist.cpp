#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 310;

char grid[MAXN][MAXN];
int ans[2 * MAXN];
int acc[2 * MAXN][MAXN];

void solve_diag(int n, int m) {
    memset(acc, 0, sizeof(acc));
    for (int d = 2; d <= n + m; d++) {
        for (int c = 1; c <= m; c++) {
            int r = d - c;
            if (r < 1) break;
            if (r > n) continue;
            acc[d][c] = acc[d][c - 1] + (grid[r][c] == '1');
        }
    }

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (grid[r][c] == '0') continue;
            for (int dist = 1; dist <= n + m - 2; dist++) {
                int d = r + c - dist;
                if (d < 2) break;
                int c0 = max(0, c - dist), c1 = min(c - 1, d - 1);
                if (c0 < c1) {
                    ans[dist] += acc[d][c1] - acc[d][c0];
                    // debug("(%d, %d): %d at dist %d\n", r, c, acc[d][c1] - acc[d][c0], dist);
                }
            }
        }
    }
}

void flip_lr(int n, int m) {
    // debug("flip\n");
    for (int row = 1; row <= n; row++)
        for (int l = 1, r = m; l < r; l++, r--)
            swap(grid[row][l], grid[row][r]);
}

void solve_v(int n, int m) {
    for (int c = 1; c <= m; c++) {
        for (int r1 = 1; r1 <= n; r1++) {
            if (grid[r1][c] == '0') continue;
            for (int r2 = r1 + 1; r2 <= n; r2++) {
                if (grid[r2][c] == '0') continue;
                ans[r2 - r1]++;
            }
        }
    }
}

void solve_h(int n, int m) {
    for (int r = 1; r <= n; r++) {
        for (int c1 = 1; c1 <= m; c1++) {
            if (grid[r][c1] == '0') continue;
            for (int c2 = c1 + 1; c2 <= m; c2++) {
                if (grid[r][c2] == '0') continue;
                ans[c2 - c1]++;
            }
        }
    }
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, m;
        cin >> n >> m;
        for (int r = 1; r <= n; r++)
            scanf(" %s", &grid[r][1]);

        memset(ans, 0, sizeof(ans));
        solve_diag(n, m);
        flip_lr(n, m);
        solve_diag(n, m);
        solve_v(n, m);
        solve_h(n, m);
        for (int i = 1; i <= n + m - 2; i++)
            printf("%d%c", ans[i], i == n + m - 2 ? '\n' : ' ');        
    }
             
    return 0;
}
