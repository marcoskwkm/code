#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 30;

char grid[MAXN][MAXN];
bool in_piece[MAXN][MAXN];
bool seen[MAXN][MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int n, m;

int dfs(int r, int c) {
    int ret = 1;
    seen[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
        if (!seen[nr][nc] && in_piece[nr][nc]) ret += dfs(nr, nc);
    }
    return ret;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        memset(grid, 0, sizeof(grid));
        scanf("%d%d", &n, &m);
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                scanf(" %c", &grid[r][c]);
        int ans = 0;
        for (int mask = 1; mask < (1 << (n * m)); mask++) {
            memset(in_piece, 0, sizeof(in_piece));
            memset(seen, 0, sizeof(seen));
            int sr = -1, sc = -1;
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    if (mask & (1 << (r * m + c))) {
                        in_piece[r][c] = 1;
                        sr = r, sc = c;
                    }
                }
            }
            if (dfs(sr, sc) != __builtin_popcount(mask))
                continue;
            bool ok = 0;
            for (int mr = 0; mr <= n; mr++) {
                for (int mc = 0; mc <= m; mc++) {
                    char c0 = 0, c1 = 0, c2 = 0, c3 = 0;
                    bool f = 1;
                    for (int r = 0; r < n; r++) {
                        for (int c = 0; c < m; c++) {
                            if (!in_piece[r][c]) continue;
                            if (r < mr && c < mc) {
                                if (!c0) c0 = grid[r + 1][c + 1];
                                else if (grid[r + 1][c + 1] != c0) f = 0;
                            }
                            else if (r < mr && c >= mc) {
                                if (!c1) c1 = grid[r + 1][c + 1];
                                else if (grid[r + 1][c + 1] != c1) f = 0;
                            }
                            else if(r >= mr && c < mc) {
                                if (!c2) c2 = grid[r + 1][c + 1];
                                else if (grid[r + 1][c + 1] != c2) f = 0;
                            }
                            else {
                                if (!c3) c3 = grid[r + 1][c + 1];
                                else if (grid[r + 1][c + 1] != c3) f = 0;
                            }
                        }
                    }
                    if (!f) continue;
                    f = 0;
                    for (int r = 0; r <= n; r++) {
                        for (int c = 0; c <= m; c++) {
                            bool f2 = 1;
                            if (grid[r][c] != c0) f2 = 0;
                            if (grid[r][c + 1] != c1) f2 = 0;
                            if (grid[r + 1][c] != c2) f2 = 0;
                            if (grid[r + 1][c + 1] != c3) f2 = 0;
                            if (f2) f = 1;
                        }
                    }
                    if (f) ok = 1;
                }
            }
            if (ok) ans = max(ans, __builtin_popcount(mask));
        }
        printf("Case #%d: %d\n", t, ans);
    }        
    return 0;
}
