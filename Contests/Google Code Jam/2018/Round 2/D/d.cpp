#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<char, char, char, char> Square;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 30;

char grid[MAXN][MAXN];
bool seen[MAXN][MAXN];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int n, m;

int dfs(int r, int c, int mr, int mc, char c0, char c1, char c2, char c3) {
    if (r < mr && c < mc && grid[r][c] != c0) return 0;
    if (r < mr && c >= mc && grid[r][c] != c1) return 0;
    if (r >= mr && c < mc && grid[r][c] != c2) return 0;
    if (r >= mr && c >= mc && grid[r][c] != c3) return 0;
    int ret = 1;
    seen[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
        if (!seen[nr][nc]) ret += dfs(nr, nc, mr, mc, c0, c1, c2, c3);
    }
    return ret;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        scanf("%d%d", &n, &m);
        set<Square> s;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                scanf(" %c", &grid[r][c]);
        for (int r = 0; r + 1 < n; r++)
            for (int c = 0; c + 1 < m; c++)
                s.insert(Square(grid[r][c], grid[r][c + 1], grid[r + 1][c], grid[r + 1][c + 1]));
        int ans = 0;
        for (int mr = 0; mr <= n; mr++) {
            for (int mc = 0; mc <= m; mc++) {
                for (char c0: {'B', 'W'}) {
                    for (char c1: {'B', 'W'}) {
                        for (char c2: {'B', 'W'}) {
                            for (char c3: {'B', 'W'}) {
                                if (0 < mr && mr < n && 0 < mc && mc < m && s.find(Square(c0, c1, c2, c3)) == s.end()) continue;
                                memset(seen, 0, sizeof(seen));
                                for (int r = 0; r < n; r++) {
                                    for (int c = 0; c < m; c++) {
                                        if (!seen[r][c])
                                            ans = max(ans, dfs(r, c, mr, mc, c0, c1, c2, c3));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }        
        printf("Case #%d: %d\n", t, ans);
    }        
    return 0;
}
